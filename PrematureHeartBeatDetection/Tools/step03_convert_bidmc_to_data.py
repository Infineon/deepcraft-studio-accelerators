"""Beat extraction used by step04_prepare_dataset.py.

Reads WFDB channel 0 and the ``.ecg`` annotations, cuts a mid-RR window
around each beat, and linearly interpolates that window to 140 samples.
Step 04 packs those beats (at most 300 per session) and writes the labels.
``write_session`` is a one-beat helper and is not the shipped Data/ layout.
"""

from __future__ import annotations

import random
import uuid
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path

import numpy as np
import wfdb

from step01_download_bidmc import RECORDS
from step02_ecg_classes import CLASS_NAMES, map_symbol

BEAT_LENGTH = 140
SOURCE_HZ = 250.0
MIN_SEGMENT = 12
FILETIME_EPOCH_DIFF = 62135596800


@dataclass
class Beat:
    record: str
    index: int
    symbol: str
    cls: str
    left: int
    right: int
    samples: np.ndarray | None = None  # shape (140,) after materialize


@dataclass
class SessionFiles:
    name: str
    session_id: str
    dataset_folder: str
    subject_id: str
    cls: str
    data_path: Path
    label_path: Path
    session_path: Path
    sample_rate_hz: int
    start_time: float
    duration_sec: float
    modified_ticks: int
    label_duration_sec: float


def filetime_ticks(path: Path) -> int:
    """File modification time as .NET ticks, the format the ``.improj`` stores."""
    return int((path.stat().st_mtime + FILETIME_EPOCH_DIFF) * 10_000_000)


def interpolate_beat(segment: np.ndarray, length: int = BEAT_LENGTH) -> np.ndarray:
    """Linear resample with both endpoints kept. Firmware must match this."""
    if len(segment) == length:
        return segment.astype(np.float64)
    src = np.linspace(0.0, 1.0, num=len(segment), endpoint=True)
    dst = np.linspace(0.0, 1.0, num=length, endpoint=True)
    return np.interp(dst, src, segment.astype(np.float64))


def extract_record_beats(record_path: Path, channel: int = 0) -> list[Beat]:
    """List every usable beat in one record with its mid-RR sample bounds.

    Reads only the header and the ``.ecg`` annotations, so this is cheap.
    Each beat spans from the midpoint to the previous annotation to the
    midpoint to the next one. Non-beat markers and cuts shorter than
    ``MIN_SEGMENT`` are skipped. Samples are loaded later by
    ``materialize_beats`` for the beats that survive selection.
    """
    rec = wfdb.rdheader(str(record_path))
    sig_len = int(rec.sig_len)
    ann = wfdb.rdann(str(record_path), "ecg")
    samples = np.asarray(ann.sample, dtype=np.int64)
    symbols = list(ann.symbol)
    n = len(samples)
    beats: list[Beat] = []
    # First and last annotations have no neighbor on one side, so no mid-RR cut.
    for i in range(1, n - 1):
        cls = map_symbol(symbols[i])
        if cls is None:
            continue
        left = int((samples[i - 1] + samples[i]) // 2)
        right = int((samples[i] + samples[i + 1]) // 2)
        if right <= left + MIN_SEGMENT:
            continue
        left = max(0, left)
        right = min(sig_len, right)
        if right - left < MIN_SEGMENT:
            continue
        beats.append(
            Beat(
                record=record_path.name,
                index=i,
                symbol=symbols[i],
                cls=cls,
                left=left,
                right=right,
            )
        )
    return beats


def materialize_beats(chfdb_dir: Path, beats: list[Beat], channel: int = 0) -> None:
    """Load the millivolt signal once per record and fill ``Beat.samples``.

    Uses ``p_signal`` (ADC counts already scaled by the header gain) from the
    requested channel, cuts ``[left, right)``, and interpolates to 140 points.
    """
    by_record: dict[str, list[Beat]] = defaultdict(list)
    for beat in beats:
        by_record[beat.record].append(beat)
    for rec_name, rec_beats in by_record.items():
        print(f"Interpolating {len(rec_beats)} beats from {rec_name} ...")
        rec = wfdb.rdrecord(str(chfdb_dir / rec_name), channels=[channel])
        signal = np.asarray(rec.p_signal[:, 0], dtype=np.float64)
        for beat in rec_beats:
            segment = signal[beat.left : beat.right]
            beat.samples = interpolate_beat(segment)


def extract_all_beats(chfdb_dir: Path, records: list[str], channel: int = 0) -> list[Beat]:
    """Run ``extract_record_beats`` over all records and print per-class counts."""
    all_beats: list[Beat] = []
    for rec in records:
        path = chfdb_dir / rec
        if not (chfdb_dir / f"{rec}.dat").is_file():
            raise FileNotFoundError(f"Missing {rec}.dat under {chfdb_dir}")
        print(f"Extracting beats from {rec} ...")
        rec_beats = extract_record_beats(path, channel=channel)
        counts = Counter(b.cls for b in rec_beats)
        print(f"  {len(rec_beats)} beats  {dict(counts)}")
        all_beats.extend(rec_beats)
    return all_beats


def stratified_subsample(
    beats: list[Beat],
    *,
    max_beats: int,
    seed: int,
) -> list[Beat]:
    """Keep all rare beats; downsample majority classes to hit max_beats."""
    rng = random.Random(seed)
    by_class: dict[str, list[Beat]] = defaultdict(list)
    for beat in beats:
        by_class[beat.cls].append(beat)

    if max_beats <= 0 or len(beats) <= max_beats:
        out = list(beats)
        rng.shuffle(out)
        return out

    n_classes = len([c for c in CLASS_NAMES if by_class[c]])
    budget = max(1, max_beats // max(n_classes, 1))
    chosen: list[Beat] = []
    leftover_budget = max_beats

    # First pass: take up to `budget` per class (or all if fewer).
    remainder: dict[str, list[Beat]] = {}
    for cls in CLASS_NAMES:
        pool = list(by_class[cls])
        rng.shuffle(pool)
        take = min(len(pool), budget)
        chosen.extend(pool[:take])
        remainder[cls] = pool[take:]
        leftover_budget -= take

    # Fill leftover from remaining majority beats, still shuffled.
    rest = []
    for cls in CLASS_NAMES:
        rest.extend(remainder[cls])
    rng.shuffle(rest)
    if leftover_budget > 0:
        chosen.extend(rest[:leftover_budget])

    rng.shuffle(chosen)
    return chosen[:max_beats]


def _time_axis(n: int, hz: float) -> np.ndarray:
    """Timestamps for ``n`` samples starting at one sample period (0.004 s)."""
    step = 1.0 / hz
    return np.arange(n, dtype=np.float64) * step + step


def write_session(beat: Beat, data_dir: Path, session_id: str | None = None) -> SessionFiles:
    """Write one beat as its own session. Step 04 packs many beats per file instead."""
    if beat.samples is None:
        raise ValueError(f"Beat {beat.record}:{beat.index} has no samples; call materialize_beats first")
    name = f"{beat.record}_b{beat.index:06d}_{beat.cls}"
    session_dir = data_dir / beat.record / name
    data_path = session_dir / "ECG.data"
    label_path = session_dir / "label.label"
    session_path = session_dir / f"{name}.imsession"
    session_dir.mkdir(parents=True, exist_ok=True)

    times = _time_axis(len(beat.samples), SOURCE_HZ)
    with data_path.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write("# Time (seconds),ECG\n")
        for t, v in zip(times, beat.samples):
            handle.write(f"{t:.7f},{v:.8f}\n")

    duration = float(times[-1])
    start = float(times[0])
    with label_path.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write(
            "Time(Seconds),Length(Seconds),Label(string),Confidence(double),Comment(string)\n"
        )
        handle.write(f"{start:.7f},{duration:.7f},{beat.cls},1,\n")

    sid = session_id or str(uuid.uuid4())
    session_path.write_text(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<ImagimobStudio version="0.9">
  <Timeline id="{sid}">
    <Tracks>
      <Track name="ECG Data" type="datacsv" isLabelTrack="False">
        <PayloadFile>ECG.data</PayloadFile>
        <Shape>
          <Axis name="Channel" size="1">
            <Label index="0">ECG</Label>
          </Axis>
        </Shape>
      </Track>
      <Track name="label" type="labelcsv">
        <PayloadFile>label.label</PayloadFile>
        <Shape>
          <Axis name="Labels" size="1">
            <Label index="0">{beat.cls}</Label>
          </Axis>
        </Shape>
      </Track>
    </Tracks>
  </Timeline>
</ImagimobStudio>
""",
        encoding="utf-8",
    )
    return SessionFiles(
        name=name,
        session_id=sid,
        dataset_folder=beat.record,
        subject_id=beat.record,
        cls=beat.cls,
        data_path=data_path,
        label_path=label_path,
        session_path=session_path,
        sample_rate_hz=int(SOURCE_HZ),
        start_time=start,
        duration_sec=duration,
        modified_ticks=filetime_ticks(data_path),
        label_duration_sec=duration,
    )


def scan_sessions(data_dir: Path) -> list[SessionFiles]:
    """Rebuild SessionFiles records from an existing Data/ folder."""
    import xml.etree.ElementTree as ET

    sessions: list[SessionFiles] = []
    for data_path in sorted(data_dir.rglob("ECG.data")):
        session_dir = data_path.parent
        label_path = session_dir / "label.label"
        session_files = list(session_dir.glob("*.imsession"))
        if not label_path.is_file() or not session_files:
            continue
        session_path = session_files[0]

        lines = label_path.read_text(encoding="utf-8").strip().splitlines()
        if len(lines) < 2:
            continue
        parts = lines[1].split(",")
        start = float(parts[0])
        label_duration = float(parts[1])
        cls = parts[2]

        duration = start
        for line in data_path.read_text(encoding="utf-8").splitlines():
            if not line.strip() or line.startswith("#"):
                continue
            duration = float(line.split(",", 1)[0])

        session_id = str(uuid.uuid4())
        try:
            timeline = ET.parse(session_path).getroot().find("Timeline")
            if timeline is not None and timeline.get("id"):
                session_id = timeline.get("id", session_id)
        except ET.ParseError:
            pass

        sessions.append(
            SessionFiles(
                name=session_dir.name,
                session_id=session_id,
                dataset_folder=session_dir.parent.relative_to(data_dir).as_posix(),
                subject_id=session_dir.parent.name,
                cls=cls,
                data_path=data_path,
                label_path=label_path,
                session_path=session_path,
                sample_rate_hz=int(SOURCE_HZ),
                start_time=start,
                duration_sec=duration,
                modified_ticks=filetime_ticks(data_path),
                label_duration_sec=label_duration,
            )
        )
    return sessions


def write_sessions(beats: list[Beat], data_dir: Path) -> list[SessionFiles]:
    """Write one session per beat with progress output. Not used by step 04."""
    sessions = []
    for i, beat in enumerate(beats, start=1):
        sessions.append(write_session(beat, data_dir))
        if i % 500 == 0 or i == len(beats):
            print(f"  wrote {i}/{len(beats)} sessions")
    return sessions
