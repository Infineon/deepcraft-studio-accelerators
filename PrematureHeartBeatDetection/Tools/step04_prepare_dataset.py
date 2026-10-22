#!/usr/bin/env python3
"""Rebuild packed ECG sessions and refresh the existing Studio project.

Rewrites ``Data/`` and updates the session entries in
``PrematureHeartBeatDetection.improj`` and ``Resources/dataset_manifest.json``.
The selection, packing, and split are fixed by this script and the
manifest, so running it reproduces the shipped sessions. ``chf07`` and
``chf15`` stay in the test set.

Pipeline:
1. Download ``chf01``–``chf15`` from PhysioNet.
2. Cut ECG channel 0 at mid-RR boundaries and interpolate each beat to
   140 samples.
3. Keep every PVC, R-on-T PVC, and supraventricular beat, plus 100,000
   normal beats (seed 73). Drop detector-unclassified beats.
4. Pack at most 300 same-person, same-class beats per Studio session.
5. Write one ``label.label`` per session. Binary mode (default) labels
   positive sessions ``premature_beat``. Normal sessions are header-only.
   ``--label-mode three-class`` keeps the three positive names.
6. Z-score each recording on its own selected samples.
7. Refresh the ``.improj`` and the manifest.
"""

from __future__ import annotations

import argparse
import json
import math
import random
import shutil
import uuid
import xml.etree.ElementTree as ET
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path

from step01_download_bidmc import RECORDS, download_chfdb
from step03_convert_bidmc_to_data import (
    BEAT_LENGTH,
    SOURCE_HZ,
    Beat,
    extract_all_beats,
    filetime_ticks,
    materialize_beats,
)

PROJECT_DIR = Path(__file__).resolve().parent.parent
RAW_DIR = PROJECT_DIR / "Raw_Data" / "chfdb"
DATA_DIR = PROJECT_DIR / "Data"
BUILD_DIR = PROJECT_DIR / ".build"
RAW_PACKED_DIR = BUILD_DIR / "raw_packed"
PROJECT_FILE = PROJECT_DIR / "PrematureHeartBeatDetection.improj"
MANIFEST_FILE = PROJECT_DIR / "Resources" / "dataset_manifest.json"

POSITIVE_CLASSES = ("r_on_t_pvc", "pvc", "supraventricular")
LABEL_MODES = ("binary", "three-class")
LABEL_TRACK = "label"
LABEL_FILE = "label.label"
NORMAL_TARGET = 100_000
# Packing layout of the shipped Data/. Each person/class pool is first cut
# into GROUP_BEATS blocks, and each block into CHUNK_BEATS sessions, so a
# 1000-beat block becomes files of 300, 300, 300, 100. This reproduces the
# session names listed in dataset_manifest.json and the .improj.
GROUP_BEATS = 1_000
CHUNK_BEATS = 300
SEED = 73
LABEL_HEADER = (
    "Time(Seconds),Length(Seconds),Label(string),Confidence(double),Comment(string)\n"
)


@dataclass
class PackedSession:
    name: str
    record: str
    source_class: str
    beat_count: int
    duration: float
    folder: Path


def select_beats(beats: list[Beat]) -> list[Beat]:
    """Choose the beats that go into ``Data/``, reproducibly.

    Keeps every positive beat (PVC, R-on-T PVC, supraventricular). Normal
    beats are capped at ``NORMAL_TARGET`` spread evenly over the 15 records,
    shuffled with ``SEED`` so a rebuild picks the same beats as the shipped
    set. ``unclassified`` beats are dropped here.
    """
    rng = random.Random(SEED)
    selected = [beat for beat in beats if beat.cls in POSITIVE_CLASSES]
    normals: dict[str, list[Beat]] = defaultdict(list)
    for beat in beats:
        if beat.cls == "normal":
            normals[beat.record].append(beat)

    base, remainder = divmod(NORMAL_TARGET, len(RECORDS))
    for index, record in enumerate(RECORDS):
        pool = normals[record]
        rng.shuffle(pool)
        take = min(len(pool), base + (1 if index < remainder else 0))
        selected.extend(pool[:take])
    rng.shuffle(selected)
    return selected


def existing_session_ids() -> dict[str, str]:
    """Session name -> sessionId from the current ``.improj``.

    Reusing the ids keeps Studio's session identity (and any user notes)
    stable across rebuilds instead of minting new UUIDs.
    """
    tree = ET.parse(PROJECT_FILE)
    return {
        session.get("name", ""): session.get("sessionId", str(uuid.uuid4()))
        for session in tree.getroot().findall("./Database/DataSet/Session")
    }


def target_label(source_class: str, label_mode: str) -> str | None:
    """Label written to ``label.label``; None means header-only (Studio ``unlabeled``)."""
    if source_class == "normal":
        return None
    return "premature_beat" if label_mode == "binary" else source_class


def symbols_for(label_mode: str) -> tuple[str, ...]:
    """Class list for the Studio project, ``unlabeled`` first."""
    if label_mode == "binary":
        return ("unlabeled", "premature_beat")
    return ("unlabeled", "pvc", "r_on_t_pvc", "supraventricular")


def write_imsession(
    path: Path,
    session_id: str,
    source_class: str,
    label_mode: str,
) -> None:
    """Write the ``.imsession`` XML that ties ``ECG.data`` and ``label.label`` together."""
    is_normal = source_class == "normal"
    label = target_label(source_class, label_mode)
    label_axis = (
        '<Axis name="Labels" size="0" />'
        if is_normal
        else (
            '<Axis name="Labels" size="1">'
            f'<Label index="0">{label}</Label></Axis>'
        )
    )
    path.write_text(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<ImagimobStudio version="0.9">
  <Timeline id="{session_id}">
    <Tracks>
      <Track name="ECG Data" type="datacsv" isLabelTrack="False">
        <PayloadFile>ECG.data</PayloadFile>
        <Shape><Axis name="Channel" size="1"><Label index="0">ECG</Label></Axis></Shape>
      </Track>
      <Track name="{LABEL_TRACK}" type="labelcsv">
        <PayloadFile>{LABEL_FILE}</PayloadFile>
        <Shape>{label_axis}</Shape>
      </Track>
    </Tracks>
  </Timeline>
</ImagimobStudio>
""",
        encoding="utf-8",
    )


def write_label(path: Path, duration: float, label: str | None) -> None:
    """Write one label spanning the complete packed recording.

    The label starts at the first timestamp (0.004 s) and ends at the last,
    so every beat in a positive session carries the class. Normal sessions
    get only the CSV header.
    """
    with path.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write(LABEL_HEADER)
        if label is None:
            return
        start = 1 / SOURCE_HZ
        handle.write(f"{start:.7f},{duration - start:.7f},{label},1,\n")


def write_packed_session(
    record: str,
    source_class: str,
    chunk_index: int,
    beats: list[Beat],
    session_ids: dict[str, str],
    label_mode: str,
) -> PackedSession:
    """Write one packed session (unstandardized) under ``.build/raw_packed``.

    Beats are concatenated back to back at 250 Hz, so the file is
    ``len(beats) * 140`` rows and ``len(beats) * 0.56`` seconds long. Session
    name is ``<record>_<class>_<chunk index>``; ``normal`` is stored under
    ``normal_unlabeled`` to make the folder name explicit.
    """
    display_class = "normal_unlabeled" if source_class == "normal" else source_class
    name = f"{record}_{display_class}_{chunk_index:03d}"
    folder = RAW_PACKED_DIR / record / display_class / name
    folder.mkdir(parents=True, exist_ok=True)

    data_path = folder / "ECG.data"
    sample_index = 0
    with data_path.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write("# Time (seconds),ECG\n")
        for beat in beats:
            if beat.samples is None:
                raise ValueError(f"Beat not materialized: {beat.record}:{beat.index}")
            for value in beat.samples:
                sample_index += 1
                handle.write(f"{sample_index / SOURCE_HZ:.7f},{float(value):.8f}\n")

    duration = sample_index / SOURCE_HZ
    write_label(
        folder / LABEL_FILE,
        duration,
        target_label(source_class, label_mode),
    )
    write_imsession(
        folder / f"{name}.imsession",
        session_ids.get(name, str(uuid.uuid4())),
        source_class,
        label_mode,
    )
    return PackedSession(
        name=name,
        record=record,
        source_class=source_class,
        beat_count=len(beats),
        duration=duration,
        folder=folder,
    )


def pack_sessions(
    beats: list[Beat],
    session_ids: dict[str, str],
    label_mode: str,
) -> list[PackedSession]:
    """Group beats by (record, class) and write them as numbered sessions.

    Within each group the beats are cut into ``GROUP_BEATS`` blocks and each
    block into ``CHUNK_BEATS`` sessions, numbered consecutively. See the
    comment next to those constants.
    """
    groups: dict[tuple[str, str], list[Beat]] = defaultdict(list)
    for beat in beats:
        groups[(beat.record, beat.cls)].append(beat)

    sessions: list[PackedSession] = []
    for (record, source_class), pool in sorted(groups.items()):
        chunk_index = 0
        for block_start in range(0, len(pool), GROUP_BEATS):
            block = pool[block_start : block_start + GROUP_BEATS]
            for offset in range(0, len(block), CHUNK_BEATS):
                sessions.append(
                    write_packed_session(
                        record,
                        source_class,
                        chunk_index,
                        block[offset : offset + CHUNK_BEATS],
                        session_ids,
                        label_mode,
                    )
                )
                chunk_index += 1
    return sessions


def iter_values(path: Path):
    """Yield the ECG column of an ``ECG.data`` file, skipping the header."""
    with path.open(encoding="utf-8") as handle:
        for line in handle:
            if line.strip() and not line.startswith("#"):
                yield float(line.rsplit(",", 1)[1])


def record_stats() -> dict[str, dict[str, float | int]]:
    """Mean and std per record over all its selected samples in ``.build/raw_packed``.

    These are the per-person z-score parameters stored in the manifest.
    Computed over the packed beats (not the whole 20 h recording), so they
    match exactly what the network sees.
    """
    result: dict[str, dict[str, float | int]] = {}
    for record_dir in sorted(path for path in RAW_PACKED_DIR.iterdir() if path.is_dir()):
        count = 0
        total = 0.0
        total_sq = 0.0
        for data_path in record_dir.rglob("ECG.data"):
            for value in iter_values(data_path):
                count += 1
                total += value
                total_sq += value * value
        mean = total / count
        std = math.sqrt(max(total_sq / count - mean * mean, 0.0)) or 1.0
        result[record_dir.name] = {"mean": mean, "std": std, "n": count}
        print(f"{record_dir.name}: n={count} mean={mean:.6f} std={std:.6f}")
    return result


def write_zscored_tree(stats: dict[str, dict[str, float | int]]) -> None:
    """Replace ``Data/`` with a z-scored copy of ``.build/raw_packed``.

    Only ``ECG.data`` values change: ``(value - mean) / std`` using that
    record's statistics. Label and ``.imsession`` files are copied as is.
    """
    if DATA_DIR.exists():
        shutil.rmtree(DATA_DIR)
    for source in RAW_PACKED_DIR.rglob("*"):
        relative = source.relative_to(RAW_PACKED_DIR)
        destination = DATA_DIR / relative
        if source.is_dir():
            destination.mkdir(parents=True, exist_ok=True)
            continue
        destination.parent.mkdir(parents=True, exist_ok=True)
        if source.name != "ECG.data":
            shutil.copy2(source, destination)
            continue
        record = relative.parts[0]
        mean = float(stats[record]["mean"])
        std = float(stats[record]["std"])
        with source.open(encoding="utf-8") as reader, destination.open(
            "w", encoding="utf-8", newline="\n"
        ) as writer:
            for line in reader:
                if not line.strip() or line.startswith("#"):
                    writer.write(line if line.endswith("\n") else line + "\n")
                    continue
                time_s, value_s = line.strip().split(",", 1)
                writer.write(f"{time_s},{(float(value_s) - mean) / std:.8f}\n")


def configure_project_labels(root: ET.Element, label_mode: str) -> None:
    """Set the project's class list and resize every model's output layer.

    Updates ``SymbolMap``, ``LastClassCount``, each ``Network`` outshape,
    the last Dense layer's units, and the per-model ``SymbolWeights``, so
    switching between binary and three-class does not need manual edits in
    Studio.
    """
    symbols = symbols_for(label_mode)
    last_class_count = root.find("./ModelFactory/LastClassCount")
    if last_class_count is not None:
        last_class_count.text = str(len(symbols))

    symbol_map = root.find("./Database/SymbolMap")
    if symbol_map is None:
        raise RuntimeError("Project has no SymbolMap")
    for child in list(symbol_map):
        symbol_map.remove(child)
    for index, symbol in enumerate(symbols):
        ET.SubElement(
            symbol_map,
            "Symbol",
            {
                "name": symbol,
                "id": str(index),
                "weight": "2" if symbol == "unlabeled" else "1",
            },
        )

    for model in root.findall("./Models/Model"):
        network = model.find("Network")
        if network is None:
            raise RuntimeError(f"Model {model.get('name')} has no Network")
        network.set("outshape", f"[{len(symbols)}]")
        dense_units = [
            unit.find("Argument[@param='units']")
            for unit in network.findall("Unit")
            if unit.get("id") == "Core.Layers.Dense"
        ]
        dense_units[-1].text = str(len(symbols))
        weights = model.find("SymbolWeights")
        if weights is None:
            weights = ET.SubElement(model, "SymbolWeights", {"override": "False"})
        for child in list(weights):
            weights.remove(child)
        for symbol in symbols:
            ET.SubElement(
                weights,
                "SymbolWeight",
                {"symbol": symbol, "weight": "1"},
            )


def require_manifest_names(sessions: list[PackedSession]) -> dict[str, list[str]]:
    """Guard: the packed names must equal the manifest's ``split_sessions``.

    With the shipped constants this always passes. It only fires after a
    change to the selection or packing constants, and then it stops before
    ``write_zscored_tree`` replaces ``Data/``.
    """
    expected = json.loads(MANIFEST_FILE.read_text(encoding="utf-8"))["split_sessions"]
    expected_names = {name for split_names in expected.values() for name in split_names}
    generated = {session.name for session in sessions}
    if generated != expected_names:
        missing = sorted(expected_names - generated)
        extra = sorted(generated - expected_names)
        raise RuntimeError(
            "Generated sessions differ from dataset_manifest.json; "
            f"missing={missing}, extra={extra}. Data/ was not replaced."
        )
    return expected


def update_project(sessions: list[PackedSession], label_mode: str) -> None:
    """Point every ``<Session>`` in the ``.improj`` at the freshly written files.

    Session membership per split is taken from the ``.improj`` itself and
    checked against the manifest; only paths, lengths, timestamps, and label
    entries are rewritten. The train/validation/test assignment never moves.
    """
    expected = require_manifest_names(sessions)
    generated = {session.name: session for session in sessions}

    tree = ET.parse(PROJECT_FILE)
    root = tree.getroot()
    configure_project_labels(root, label_mode)
    for dataset in root.findall("./Database/DataSet"):
        split = dataset.get("id")
        if split == "unassigned":
            continue
        actual_names = [session.get("name") for session in dataset.findall("Session")]
        if actual_names != expected[split]:
            raise RuntimeError(f"{split} membership differs from dataset_manifest.json")
        for element in dataset.findall("Session"):
            packed = generated[element.get("name", "")]
            relative = packed.folder.relative_to(RAW_PACKED_DIR)
            folder = DATA_DIR / relative
            data_path = folder / "ECG.data"
            label_path = folder / LABEL_FILE
            session_path = folder / f"{packed.name}.imsession"
            # Empty normal label files use Studio's built-in unlabeled class.
            # They are valid sessions, so do not preserve stale label warnings.
            element.set("tags", "None")
            element.set("labelTrack", LABEL_TRACK)
            element.find("DataFile").text = f"/Data/{relative.as_posix()}/ECG.data"
            element.find("DataFile").set("modified", str(filetime_ticks(data_path)))
            element.find("DataFile").set("length", f"{packed.duration:.7f}")
            element.find("SessionFile").text = (
                f"/Data/{relative.as_posix()}/{session_path.name}"
            )
            element.find("LabelFile").text = (
                f"/Data/{relative.as_posix()}/{LABEL_FILE}"
            )
            element.find("LabelFile").set("modified", str(filetime_ticks(label_path)))
            labels = element.find("Labels")
            if labels is None:
                labels = ET.SubElement(element, "Labels")
            for child in list(labels):
                labels.remove(child)
            label = target_label(packed.source_class, label_mode)
            if label is not None:
                label_element = ET.SubElement(
                    labels,
                    "Label",
                    {
                        "count": "1",
                        "length": f"{packed.duration - (1 / SOURCE_HZ):.7f}",
                    },
                )
                label_element.text = label
    tree.write(PROJECT_FILE, encoding="UTF-8", xml_declaration=True)


def manifest_split_counts(
    sessions: list[PackedSession],
    split_sessions: dict[str, list[str]],
    label_mode: str,
) -> dict[str, dict[str, int]]:
    """Beats per label per split, for the ``split_beat_counts`` manifest entry."""
    by_name = {session.name: session for session in sessions}
    result: dict[str, dict[str, int]] = {}
    for split, names in split_sessions.items():
        counts: Counter[str] = Counter()
        for name in names:
            session = by_name[name]
            label = target_label(session.source_class, label_mode) or "unlabeled"
            counts[label] += session.beat_count
        result[split] = dict(counts)
    return result


def parse_args() -> argparse.Namespace:
    """Command-line flags; see Tools/README.md for the table."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--skip-download",
        action="store_true",
        help="Reuse complete files already present under Raw_Data/chfdb",
    )
    parser.add_argument(
        "--force-download",
        action="store_true",
        help="Download the PhysioNet source files again",
    )
    parser.add_argument(
        "--keep-intermediate",
        action="store_true",
        help="Keep unstandardized packed files under .build/raw_packed",
    )
    parser.add_argument(
        "--label-mode",
        choices=LABEL_MODES,
        default="binary",
        help=(
            "binary (default): unlabeled vs premature_beat; "
            "three-class: unlabeled plus pvc, r_on_t_pvc, supraventricular"
        ),
    )
    return parser.parse_args()


def main() -> int:
    """Download, extract, select, pack, check, standardize, then refresh project and manifest."""
    args = parse_args()
    if not args.skip_download:
        download_chfdb(RAW_DIR, force=args.force_download)

    if RAW_PACKED_DIR.exists():
        shutil.rmtree(RAW_PACKED_DIR)
    RAW_PACKED_DIR.mkdir(parents=True)

    beats = extract_all_beats(RAW_DIR, list(RECORDS), channel=0)
    selected = select_beats(beats)
    counts = Counter(beat.cls for beat in selected)
    print(f"Selected {len(selected)} beats: {dict(counts)}")

    materialize_beats(RAW_DIR, selected, channel=0)
    sessions = pack_sessions(selected, existing_session_ids(), args.label_mode)
    require_manifest_names(sessions)
    stats = record_stats()
    write_zscored_tree(stats)
    update_project(sessions, args.label_mode)

    manifest = json.loads(MANIFEST_FILE.read_text(encoding="utf-8"))
    manifest["normalization_stats"] = stats
    manifest["selected_counts"] = dict(counts)
    manifest["label_mode"] = args.label_mode
    manifest["symbols"] = list(symbols_for(args.label_mode))
    manifest["label_file"] = LABEL_FILE
    manifest["labels_per_positive_session"] = 1
    manifest["split_beat_counts"] = manifest_split_counts(
        sessions,
        manifest["split_sessions"],
        args.label_mode,
    )
    if args.label_mode == "binary":
        manifest["positive_classes_collapsed_to"] = "premature_beat"
    else:
        manifest.pop("positive_classes_collapsed_to", None)
    MANIFEST_FILE.write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if not args.keep_intermediate:
        shutil.rmtree(BUILD_DIR)
    print(f"Wrote {len(sessions)} Studio sessions under {DATA_DIR}")
    print(f"Updated {PROJECT_FILE}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
