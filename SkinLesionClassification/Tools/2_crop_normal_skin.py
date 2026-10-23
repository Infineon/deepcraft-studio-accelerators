"""Add the Normal_Skin group to SkinLesionClassification.improj.

Run this after 1_organize_diagnosis_folders.py, from the Tools folder:

    python 2_crop_normal_skin.py

The same photos and the same constants produce the same crops. A crop stays in
the split of the photo it was cut from and is labeled Normal_Skin, a frame
with no lesion. The Suspicious and Benign sessions already in the project stay.

A crop is kept only when all of the following hold:

- The patch is a square of at least 224 px, about one third of the shorter side.
- It does not cover the highest-contrast window in the photo (the usual lesion).
- Its color is in the skin range, with visible texture rather than a flat blur.
- No quarter of the patch is much darker or redder than the rest.
- The patch is calmer than the center of the photo.

At most two photos are taken from the same PAD-UFES-20 patient. Training keeps
the 300 patches closest to ordinary skin texture. Validation and test keep the
same share of their photos: 80 and 78 when that many clear patches exist.
"""

from __future__ import annotations

import csv
import re
import shutil
import uuid
from collections import Counter
from pathlib import Path

import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
MAPPING = ROOT / "Resources" / "rename_mapping.csv"
CROP_DIR = ROOT / "Data" / "Normal_Skin"
MANIFEST = ROOT / "Resources" / "normal_skin_crops.csv"
PROJECT_IMPROJ = ROOT / "SkinLesionClassification.improj"
COLUMN_ID = "77dea31d-4f53-4c87-8518-2e145a1dea1f"
JOB_ID = "c4e8a1d7-6b20-4f3e-8a91-5d2c7e0b4a18"
PROJECT_ID = "9f3b2c61-7a84-4d15-b6e0-1c8a5f2d7e03"
MODEL_ID = "e1d04a92-3c57-4b68-9f21-6a0c8d5e2b74"

TARGET_COUNT = 300
SPLIT_TARGETS = {"train": 300, "validation": 80, "test": 78}
BASE_COUNTS = {"train": 1716, "validation": 457, "test": 444}
MIN_SIDE = 224
CROP_FRACTION = 0.34
STD_RANGE = (6.0, 26.0)
ENERGY_RANGE = (4.5, 22.0)
DISTANCE_RANGE = (8.0, 90.0)
DARK_GAP_MAX = 40.0
GRAY_SPOT_MAX = 16.0
RED_SPOT_MAX = 26.0
TARGET_STD = 14.0
TARGET_ENERGY = 10.0
JPEG_QUALITY = 90
LABEL = "Normal_Skin"

NAMESPACE = uuid.UUID("6f1d8a0e-3c2b-4e7a-9d15-8a2c4b6e0f11")


def filetime(path: Path) -> int:
    return int((path.stat().st_mtime + 11644473600) * 10_000_000)


def person_key(row: dict[str, str]) -> str:
    patient = row["patient_id"].strip()
    if patient:
        return row["source"] + ":" + patient
    return row["source"] + ":" + Path(row["current_path"]).stem


def features(arr: np.ndarray) -> dict[str, float | bool | np.ndarray]:
    red = arr[:, :, 0].astype(np.float32)
    green = arr[:, :, 1].astype(np.float32)
    blue = arr[:, :, 2].astype(np.float32)
    gray = 0.299 * red + 0.587 * green + 0.114 * blue
    gy, gx = np.gradient(gray)
    mean_r, mean_g, mean_b = float(red.mean()), float(green.mean()), float(blue.mean())
    median = float(np.median(gray))
    return {
        "rgb": np.array([mean_r, mean_g, mean_b], dtype=np.float32),
        "std": float(gray.std()),
        "energy": float((np.abs(gx) + np.abs(gy)).mean()),
        "dark_gap": median - float(np.percentile(gray, 2)),
        "skin": bool(
            mean_r > mean_g - 8
            and mean_g > mean_b - 8
            and 70 < mean_r < 220
            and 12 < (mean_r - mean_b) < 120
        ),
    }


def lesion_peak(arr: np.ndarray) -> tuple[int, int, float]:
    gray = arr.mean(axis=2).astype(np.float32)
    step = max(8, min(arr.shape[:2]) // 24)
    height = gray.shape[0] // step * step
    width = gray.shape[1] // step * step
    tiles = gray[:height, :width].reshape(height // step, step, width // step, step)
    spread = tiles.std(axis=(1, 3))
    row, col = np.unravel_index(int(np.argmax(spread)), spread.shape)
    return int(row * step + step // 2), int(col * step + step // 2), float(spread[row, col])


def spot_gap(arr: np.ndarray) -> tuple[float, float]:
    gray = arr.mean(axis=2).astype(np.float32)
    red = arr[:, :, 0].astype(np.float32)
    gray_median = float(np.median(gray))
    red_median = float(np.median(red))
    gray_gap = 0.0
    red_gap = 0.0
    cells = 4
    height, width = gray.shape
    for row in range(cells):
        for col in range(cells):
            y0, y1 = row * height // cells, (row + 1) * height // cells
            x0, x1 = col * width // cells, (col + 1) * width // cells
            gray_gap = max(gray_gap, abs(float(gray[y0:y1, x0:x1].mean()) - gray_median))
            red_gap = max(red_gap, abs(float(red[y0:y1, x0:x1].mean()) - red_median))
    return gray_gap, red_gap


def candidates(height: int, width: int, side: int) -> list[tuple[str, int, int]]:
    return [
        ("top_left", 0, 0),
        ("top_right", 0, width - side),
        ("bottom_left", height - side, 0),
        ("bottom_right", height - side, width - side),
        ("top", 0, (width - side) // 2),
        ("bottom", height - side, (width - side) // 2),
        ("left", (height - side) // 2, 0),
        ("right", (height - side) // 2, width - side),
    ]


def best_crop(arr: np.ndarray) -> dict | None:
    height, width = arr.shape[:2]
    short = min(height, width)
    side = min(max(MIN_SIDE, int(short * CROP_FRACTION)), short // 2)
    if side < MIN_SIDE or height < side or width < side:
        return None
    peak_y, peak_x, peak_std = lesion_peak(arr)
    center_y, center_x = (height - side) // 2, (width - side) // 2
    center = features(arr[center_y : center_y + side, center_x : center_x + side])
    best: dict | None = None
    for name, top, left in candidates(height, width, side):
        if top <= peak_y < top + side and left <= peak_x < left + side:
            continue
        patch = arr[top : top + side, left : left + side]
        feat = features(patch)
        if not feat["skin"]:
            continue
        if not STD_RANGE[0] <= float(feat["std"]) <= STD_RANGE[1]:
            continue
        if not ENERGY_RANGE[0] <= float(feat["energy"]) <= ENERGY_RANGE[1]:
            continue
        gray_gap, red_gap = spot_gap(patch)
        if float(feat["dark_gap"]) > DARK_GAP_MAX or gray_gap > GRAY_SPOT_MAX or red_gap > RED_SPOT_MAX:
            continue
        distance = float(np.linalg.norm(feat["rgb"] - center["rgb"]))
        if not DISTANCE_RANGE[0] <= distance <= DISTANCE_RANGE[1]:
            continue
        if float(feat["std"]) > max(peak_std, float(center["std"])) * 0.75:
            continue
        score = (
            -abs(float(feat["std"]) - TARGET_STD)
            - abs(float(feat["energy"]) - TARGET_ENERGY) * 0.15
            - gray_gap * 0.05
        )
        if best is None or score > best["score"]:
            best = {
                "score": score,
                "corner": name,
                "top": top,
                "left": left,
                "side": side,
                "distance": distance,
                "std": float(feat["std"]),
                "center_std": float(center["std"]),
                "energy": float(feat["energy"]),
                "spot_gap": gray_gap,
            }
    return best


def load_candidates(split: str = "train") -> list[dict]:
    found = []
    with MAPPING.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row["split"] != split:
                continue
            with Image.open(ROOT / row["current_path"]) as image:
                arr = np.asarray(image.convert("RGB"))
            crop = best_crop(arr)
            if crop is None:
                continue
            found.append({**row, **crop})
    found.sort(key=lambda item: (-item["score"], Path(item["current_path"]).stem))
    return found


def select_crops(
    found: list[dict], target: int = TARGET_COUNT, allow_short: bool = False
) -> tuple[list[dict], int]:
    best: list[dict] = []
    best_cap = 2
    for cap in (2, 3, 4):
        counts: Counter[str] = Counter()
        chosen = []
        for item in found:
            key = person_key(item)
            if counts[key] >= cap:
                continue
            counts[key] += 1
            chosen.append(item)
            if len(chosen) == target:
                return chosen, cap
        if len(chosen) > len(best):
            best = chosen
            best_cap = cap
    if allow_short and best:
        return best, best_cap
    raise SystemExit(
        f"Found {len(found)} clear patches, which is fewer than {target} "
        "after the per-patient cap."
    )


def write_session(name: str, session_id: str) -> None:
    label_path = CROP_DIR / f"{name}.labelxml"
    session_path = CROP_DIR / f"{name}.imsession"
    label_path.write_text(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<Annotations>
  <Annotation>
    <Object>
      <Name>{LABEL}</Name>
    </Object>
  </Annotation>
</Annotations>
""",
        encoding="utf-8",
    )
    session_path.write_text(
        f"""<?xml version="1.0" encoding="UTF-8"?>
<ImagimobStudio version="0.9">
  <Timeline id="{session_id}">
    <Tracks>
      <Track name="image" type="imagejpg">
        <PayloadFile>{name}.jpg</PayloadFile>
        <Shape />
      </Track>
      <Track name="label" type="labelxml">
        <PayloadFile>{name}.labelxml</PayloadFile>
        <Shape />
      </Track>
    </Tracks>
  </Timeline>
</ImagimobStudio>
""",
        encoding="utf-8",
    )


def manifest_row(item: dict, name: str) -> dict[str, str]:
    return {
        "output_name": name,
        "source_path": item["current_path"],
        "patient_id": item["patient_id"],
        "source": item["source"],
        "issue": item["issue"],
        "split": item["split"],
        "corner": item["corner"],
        "top": item["top"],
        "left": item["left"],
        "side": item["side"],
        "score": f"{item['score']:.4f}",
        "color_distance": f"{item['distance']:.2f}",
        "patch_std": f"{item['std']:.2f}",
        "center_std": f"{item['center_std']:.2f}",
    }


def write_crops(chosen: list[dict]) -> list[dict[str, str]]:
    rows = []
    for item in chosen:
        name = "normal_" + Path(item["current_path"]).stem
        session = str(uuid.uuid5(NAMESPACE, "session:" + name))
        with Image.open(ROOT / item["current_path"]) as image:
            arr = np.asarray(image.convert("RGB"))
        patch = arr[
            item["top"] : item["top"] + item["side"],
            item["left"] : item["left"] + item["side"],
        ]
        Image.fromarray(patch).save(CROP_DIR / f"{name}.jpg", quality=JPEG_QUALITY)
        write_session(name, session)
        rows.append(manifest_row(item, name))
    return rows


def project_session(row: dict[str, str]) -> str:
    name = row["output_name"]
    text = (CROP_DIR / f"{name}.imsession").read_text(encoding="utf-8")
    match = re.search(r'<Timeline id="([^"]+)"', text)
    if match is None:
        raise SystemExit(f"missing Timeline id in {name}.imsession")
    image_path = CROP_DIR / f"{name}.jpg"
    label_path = CROP_DIR / f"{name}.labelxml"
    path = f"/Data/Normal_Skin/{name}"
    return f"""      <Session name="{name}" sessionId="{match.group(1)}" originalSessionId="00000000-0000-0000-0000-000000000000" ownerLocked="False" labelTrack="label" dataTrack="image" tags="None">
        <DataFile shape="[{row['side']},{row['side']},3]" samplerate="0" modified="{filetime(image_path)}">{path}.jpg</DataFile>
        <SessionFile>{path}.imsession</SessionFile>
        <LabelFile modified="{filetime(label_path)}">{path}.labelxml</LabelFile>
        <Labels>
          <Label count="1" length="0">{LABEL}</Label>
        </Labels>
        <CustomColumnValues>
          <CustomColumnValue columnId="{COLUMN_ID}">{LABEL}</CustomColumnValue>
        </CustomColumnValues>
      </Session>
"""


def write_project(rows: list[dict[str, str]]) -> None:
    text = PROJECT_IMPROJ.read_text(encoding="utf-8")
    if "<LastClassCount>3</LastClassCount>" in text:
        replacements = (
            ("5c518a1d-c622-11f1-8c46-9f2b40f6b5c9", JOB_ID),
            ("2d1e54ad-183d-40b4-8f46-268d8921da46", PROJECT_ID),
            ("e52000f9-da5b-4b10-99bc-a7551b2898f0", MODEL_ID),
            ("<LastClassCount>3</LastClassCount>", "<LastClassCount>4</LastClassCount>"),
            ('outshape="[3]"', 'outshape="[4]"'),
            ('inshape="[128,3]"', 'inshape="[128,4]"'),
            ('outshape="[128,3]"', 'outshape="[128,4]"'),
            (
                '        <SymbolWeight symbol="Benign" weight="1" />\n',
                '        <SymbolWeight symbol="Benign" weight="1" />\n'
                '        <SymbolWeight symbol="Normal_Skin" weight="1" />\n',
            ),
            (
                '      <Symbol name="Benign" id="2" weight="1" />\n',
                '      <Symbol name="Benign" id="2" weight="1" />\n'
                '      <Symbol name="Normal_Skin" id="3" weight="1" />\n',
            ),
        )
        for old, new in replacements:
            count = text.count(old)
            if count != 1:
                raise SystemExit(f"expected one occurrence of {old!r}, found {count}")
            text = text.replace(old, new, 1)
    elif "<LastClassCount>4</LastClassCount>" in text:
        for expected in (JOB_ID, PROJECT_ID, MODEL_ID):
            if text.count(expected) != 1:
                raise SystemExit(f"expected one occurrence of {expected}, found {text.count(expected)}")
        text = re.sub(
            r'      <Session name="normal_[^"]+".*?      </Session>\n',
            "",
            text,
            flags=re.S,
        )
    else:
        raise SystemExit("project must contain the Suspicious and Benign setup")
    grouped: dict[str, list[dict[str, str]]] = {split: [] for split in SPLIT_TARGETS}
    for row in rows:
        grouped[row["split"]].append(row)
    totals = {split: BASE_COUNTS[split] + len(grouped[split]) for split in BASE_COUNTS}
    grand = sum(totals.values())
    markers = {
        "train": "    </DataSet>\n    <DataSet id=\"validation\"",
        "validation": "    </DataSet>\n    <DataSet id=\"test\"",
        "test": "    </DataSet>\n  </Database>",
    }
    for split, marker in markers.items():
        if text.count(marker) != 1:
            raise SystemExit(f"expected one close marker for {split}")
        size = f"{totals[split] / grand:.4f}"
        text, replaced = re.subn(
            rf'(<DataSet id="{split}" targetSize=")[0-9.]+',
            rf"\g<1>{size}",
            text,
            count=1,
        )
        if replaced != 1:
            raise SystemExit(f"could not set target size for {split}")
        text = text.replace(marker, "".join(project_session(row) for row in grouped[split]) + marker, 1)
    PROJECT_IMPROJ.write_text(text, encoding="utf-8")
    print(f"Wrote {PROJECT_IMPROJ}")
    print("sessions", text.count("<Session name="))
    for split in SPLIT_TARGETS:
        print(f"{split} normal skin {len(grouped[split])}, dataset size {totals[split]}")


def main() -> None:
    if CROP_DIR.exists():
        shutil.rmtree(CROP_DIR)
    CROP_DIR.mkdir(parents=True)
    rows: list[dict[str, str]] = []
    for split, target in SPLIT_TARGETS.items():
        found = load_candidates(split)
        chosen, cap = select_crops(found, target, allow_short=split != "train")
        rows.extend(write_crops(chosen))
        print(f"{split}: wrote {len(chosen)} crops from {len(found)} clear patches, cap {cap}")
    with MANIFEST.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    write_project(rows)
    print(f"Manifest: {MANIFEST}")


if __name__ == "__main__":
    main()
