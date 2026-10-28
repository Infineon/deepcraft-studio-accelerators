"""Build the Skin Lesion Classification lesion data from the published datasets.

PAD-UFES-20 photos come from the Hugging Face mirror of the Mendeley release.
FLUO-SC clinical photos come from the CLI zip (melanoma and squamous cell only).
Hospital Italiano clinical photos come from ISIC collection 251. Dermoscopic
photos are left out. The extra clinical photos are the diagnoses grouped as
Suspicious: melanoma, basal cell carcinoma, squamous cell carcinoma, and
actinic keratosis.

Each diagnosis is grouped into Suspicious or Benign. The script writes Data/
and SkinLesionClassification.improj. Run it from the Tools folder:

    python 1_organize_diagnosis_folders.py

Re-running it stops when those outputs already exist. 2_crop_normal_skin.py
then adds the Normal_Skin group to the same project file.
"""

from __future__ import annotations

import csv
import hashlib
import io
import json
import random
import shutil
import struct
import time
import uuid
import zlib
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import requests
from PIL import Image, ImageOps

ROOT = Path(__file__).resolve().parents[1]
DEST_DATA = ROOT / "Data"
DEST_IMPROJ = ROOT / "SkinLesionClassification.improj"
DEST_MAPPING = ROOT / "Resources" / "rename_mapping.csv"
STAGING = ROOT / "_staging"

HF_API = "https://huggingface.co/api/datasets/SalmaneExploring/pad-ufes-20"
HF_FILE = "https://huggingface.co/datasets/SalmaneExploring/pad-ufes-20/resolve/main/"
FLUO_ZIP = "https://huggingface.co/datasets/Matheusbecali/FLUO-SC/resolve/main/data/CLI.zip"
HIBA_SEARCH = "https://api.isic-archive.com/api/v2/images/search/"

COLUMN_ID = "77dea31d-4f53-4c87-8518-2e145a1dea1f"
SESSION_NAMESPACE = uuid.UUID("a3c91e20-7b44-4d18-9e6f-2c5a8b1d0e47")
MAX_LONG_SIDE = 1280
JPEG_QUALITY = 90
HASH_DISTANCE = 12
SPLIT_SEED = 42

ISSUE_BY_CODE = {
    "MEL": ("Suspicious", "Melanoma"),
    "BCC": ("Suspicious", "Basal_Cell_Carcinoma"),
    "SCC": ("Suspicious", "Squamous_Cell_Carcinoma"),
    "ACK": ("Suspicious", "Actinic_Keratosis"),
    "NEV": ("Benign", "Nevus"),
    "SEK": ("Benign", "Seborrheic_Keratosis"),
}
RARE_FIRST = (
    "Melanoma",
    "Squamous_Cell_Carcinoma",
    "Seborrheic_Keratosis",
    "Nevus",
    "Actinic_Keratosis",
    "Basal_Cell_Carcinoma",
)
FLUO_FOLDERS = {"MEL": "Melanoma", "CCE": "Squamous_Cell_Carcinoma"}
HIBA_LABELS = {
    "Basal cell carcinoma": "Basal_Cell_Carcinoma",
    "Squamous cell carcinoma": "Squamous_Cell_Carcinoma",
    "Squamous cell carcinoma, NOS": "Squamous_Cell_Carcinoma",
    "Melanoma Invasive": "Melanoma",
    "Melanoma in situ": "Melanoma",
    "Melanoma, NOS": "Melanoma",
    "Melanoma": "Melanoma",
    "Actinic keratosis": "Actinic_Keratosis",
    "Solar or actinic keratosis": "Actinic_Keratosis",
}
PAPER_COUNTS = {"BCC": 845, "ACK": 730, "NEV": 244, "SEK": 235, "SCC": 192, "MEL": 52}
PAD_SPLIT_COUNTS = {
    ("Suspicious", "train"): 1114,
    ("Benign", "train"): 283,
    ("Suspicious", "validation"): 355,
    ("Benign", "validation"): 102,
    ("Suspicious", "test"): 350,
    ("Benign", "test"): 94,
}
FLUO_KEPT = {"Melanoma": 18, "Squamous_Cell_Carcinoma": 78}
HIBA_KEPT = {
    "Melanoma": 57,
    "Squamous_Cell_Carcinoma": 46,
    "Basal_Cell_Carcinoma": 103,
    "Actinic_Keratosis": 17,
}

LABELXML = """<?xml version="1.0" encoding="UTF-8"?>
<Annotations>
  <Annotation>
    <Object>
      <Name>{label}</Name>
    </Object>
  </Annotation>
</Annotations>
"""

IMSESSION = """<?xml version="1.0" encoding="UTF-8"?>
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
"""

IMPROJ_HEADER = """<?xml version="1.0" encoding="UTF-8"?>
<ImagimobStudio version="1.1.0">
  <Job id="5c518a1d-c622-11f1-8c46-9f2b40f6b5c9" />
  <ProjectType>ImageClassification</ProjectType>
  <ProjectId>2d1e54ad-183d-40b4-8f46-268d8921da46</ProjectId>
  <ModelFactory>
    <Epochs>100</Epochs>
    <BatchSize>64</BatchSize>
    <SplitCount>16</SplitCount>
    <Patience>50</Patience>
    <AppendModels>False</AppendModels>
    <LossFunction>CategoricalCrossentropy</LossFunction>
    <HardwareType>Infineon</HardwareType>
    <TrainingEnvironment>
    </TrainingEnvironment>
    <ModelFamily>Conv1D</ModelFamily>
    <ModelFlavor>SmallKern</ModelFlavor>
    <ClassifierType>GlobalAveragePool</ClassifierType>
    <Optimization>Balanced</Optimization>
    <Pooling>True</Pooling>
    <Downscale>False</Downscale>
    <LearnRate>Mid</LearnRate>
    <RegularizationFactor>Low</RegularizationFactor>
    <LastNetworkInputShape>[10]</LastNetworkInputShape>
    <LastClassCount>3</LastClassCount>
    <Optimizer>
      <LearningRate>0.001</LearningRate>
      <WeightDecay>0.0001</WeightDecay>
    </Optimizer>
    <BuildSteps>
      <Training />
      <ConfusionMatrix />
    </BuildSteps>
    <YoloVersion>yolo26n</YoloVersion>
    <ImageSize>224</ImageSize>
    <Augmentation>
      <Degrees>10</Degrees>
      <Translate>0.12</Translate>
      <Scale>0.2</Scale>
      <Shear>0</Shear>
      <FlipLeftRight>0.5</FlipLeftRight>
      <FlipUpDown>0.5</FlipUpDown>
      <Perspective>0</Perspective>
      <Bgr>0</Bgr>
      <Mosaic>0</Mosaic>
      <Mixup>0</Mixup>
      <CopyPasteMode>Flip</CopyPasteMode>
      <CopyPaste>0</CopyPaste>
      <HsvSaturation>0.25</HsvSaturation>
      <HsvValue>0.45</HsvValue>
      <HsvHue>0.008</HsvHue>
    </Augmentation>
    <AdvancedOptions>
      <Optimizer>Auto</Optimizer>
      <LearningRateInitial>0.1</LearningRateInitial>
      <LearningRateFinal>0.1</LearningRateFinal>
      <Momentum>0.937</Momentum>
      <WeightDecay>0.0005</WeightDecay>
      <ConfidenceThresholdValidation>0.001</ConfidenceThresholdValidation>
      <ConfidenceThresholdPrediction>0.25</ConfidenceThresholdPrediction>
      <IouThreshold>0.7</IouThreshold>
      <ImageWeights>False</ImageWeights>
      <TrainingMode>Training</TrainingMode>
      <FreezeLayers>10</FreezeLayers>
    </AdvancedOptions>
    <IsNasEnabled>False</IsNasEnabled>
  </ModelFactory>
  <Models>
    <Model name="yolo26n-size224-batch64-epoch100" id="e52000f9-da5b-4b10-99bc-a7551b2898f0">
      <LossFunction>CategoricalCrossentropy</LossFunction>
      <Epochs>100</Epochs>
      <BatchSize>64</BatchSize>
      <SplitCount>16</SplitCount>
      <Patience>40</Patience>
      <TrainingEnvironment>
      </TrainingEnvironment>
      <Optimizer>
        <LearningRate>0.001</LearningRate>
        <WeightDecay>0.0001</WeightDecay>
      </Optimizer>
      <Network inshape="[609,609,3]" intype="Float32" infreq="1" outshape="[3]" outtype="Float32" />
      <BuildSteps>
        <Training />
        <ConfusionMatrix />
      </BuildSteps>
      <SymbolWeights override="True">
        <SymbolWeight symbol="unlabeled" weight="1" />
        <SymbolWeight symbol="Suspicious" weight="1" />
        <SymbolWeight symbol="Benign" weight="1" />
      </SymbolWeights>
      <Preprocessor override="False" inshape="[609,609,3]" intype="Float32" infreq="0" outshape="[609,609,3]" outtype="Float32" />
      <Postprocessor override="False" inshape="[128,3]" intype="Float32" infreq="1" outshape="[128,3]" outtype="Float32" />
    </Model>
  </Models>
  <Database balance="LabelCount" redistributionScope="Everything">
    <SymbolMap>
      <Symbol name="unlabeled" id="0" weight="1" />
      <Symbol name="Suspicious" id="1" weight="1" />
      <Symbol name="Benign" id="2" weight="1" />
    </SymbolMap>
    <DataSet id="unassigned" targetSize="0" labels="Unassigned" />
"""

IMPROJ_FOOTER = """  </Database>
  <CustomColumns>
    <CustomColumn id="77dea31d-4f53-4c87-8518-2e145a1dea1f" name="Category 1" internalName="Category 1" />
  </CustomColumns>
</ImagimobStudio>
"""

EPOCH_AS_FILETIME = 116444736000000000
TICKS_PER_SECOND = 10_000_000


def fetch_bytes(url: str, headers: dict | None = None) -> bytes:
    last_error = "no attempt"
    for attempt in range(5):
        try:
            response = requests.get(url, headers=headers, timeout=120)
            if response.status_code == 200 and response.content:
                return response.content
            last_error = f"HTTP {response.status_code}"
        except requests.RequestException as exc:
            last_error = str(exc)
        time.sleep(1.5 * (attempt + 1))
    raise SystemExit(f"download failed for {url}: {last_error}")


def filetime_ticks(path: Path) -> int:
    return int(EPOCH_AS_FILETIME + path.stat().st_mtime * TICKS_PER_SECOND)


def average_hash(image: Image.Image) -> int:
    small = image.convert("L").resize((16, 16), Image.Resampling.BOX)
    pixels = list(small.getdata())
    average = sum(pixels) / len(pixels)
    value = 0
    for index, pixel in enumerate(pixels):
        if pixel >= average:
            value |= 1 << index
    return value


def too_close(value: int, hashes: list[int]) -> bool:
    return any((value ^ other).bit_count() <= HASH_DISTANCE for other in hashes)


def patient_bucket(labels: set[str]) -> str:
    for name in RARE_FIRST:
        if name in labels:
            return name
    return sorted(labels)[0]


def split_by_patient(rows: list[dict]) -> dict[str, str]:
    """Map patient_id to train, validation, or test. Every photo of that patient follows."""
    by_patient: dict[str, set[str]] = defaultdict(set)
    for row in rows:
        by_patient[row["patient_id"]].add(row["issue"])
    buckets: dict[str, list[str]] = defaultdict(list)
    for patient_id, labels in by_patient.items():
        buckets[patient_bucket(labels)].append(patient_id)

    rng = random.Random(SPLIT_SEED)
    assigned: dict[str, str] = {}
    for patients in buckets.values():
        rng.shuffle(patients)
        count = len(patients)
        train_n = int(count * 0.6)
        val_n = int(count * 0.2)
        for patient_id in patients[:train_n]:
            assigned[patient_id] = "train"
        for patient_id in patients[train_n : train_n + val_n]:
            assigned[patient_id] = "validation"
        for patient_id in patients[train_n + val_n :]:
            assigned[patient_id] = "test"
    return assigned


def pad_png_paths() -> dict[str, str]:
    payload = json.loads(fetch_bytes(HF_API))
    found: dict[str, str] = {}
    for sibling in payload.get("siblings") or []:
        name = sibling.get("rfilename") or ""
        if name.lower().endswith(".png"):
            found[name.rsplit("/", 1)[-1]] = name
    return found


def pad_jpeg(raw: bytes) -> tuple[bytes, int, int, int]:
    with Image.open(io.BytesIO(raw)) as image:
        image = ImageOps.exif_transpose(image).convert("RGB")
        image.thumbnail((MAX_LONG_SIDE, MAX_LONG_SIDE), Image.Resampling.LANCZOS)
        width, height = image.size
        buffer = io.BytesIO()
        image.save(buffer, format="JPEG", quality=JPEG_QUALITY, optimize=True)
    encoded = buffer.getvalue()
    with Image.open(io.BytesIO(encoded)) as saved:
        digest = average_hash(saved)
    return encoded, width, height, digest


def load_pad(temp_dir: Path) -> tuple[list[dict], list[int]]:
    table = list(csv.DictReader(io.StringIO(fetch_bytes(HF_FILE + "metadata.csv").decode("utf-8-sig"))))
    paths = pad_png_paths()
    print(f"PAD-UFES-20 metadata {len(table)}  png files {len(paths)}")
    prepared = []
    for row in table:
        code = (row.get("diagnostic") or "").strip()
        if code not in ISSUE_BY_CODE:
            raise SystemExit(f"unknown PAD diagnostic {code}")
        img_id = (row.get("img_id") or "").strip()
        patient_id = (row.get("patient_id") or "").strip()
        if not img_id or img_id not in paths:
            raise SystemExit(f"no PAD image for {img_id}")
        if not patient_id:
            raise SystemExit(f"{img_id} has no patient_id")
        group, issue = ISSUE_BY_CODE[code]
        prepared.append(
            {
                "img_id": img_id,
                "patient_id": patient_id,
                "code": code,
                "group": group,
                "issue": issue,
                "remote": paths[img_id],
            }
        )
    if len(prepared) != 2298:
        raise SystemExit(f"expected 2298 PAD photos, found {len(prepared)}")
    by_code = Counter(item["code"] for item in prepared)
    if dict(by_code) != PAPER_COUNTS:
        raise SystemExit(f"PAD diagnosis counts {dict(by_code)} do not match the paper")
    prepared.sort(key=lambda item: item["img_id"])
    assigned = split_by_patient(prepared)

    def fetch_one(item: dict) -> dict:
        encoded, width, height, digest = pad_jpeg(fetch_bytes(HF_FILE + item["remote"]))
        return {**item, "jpeg": encoded, "width": width, "height": height, "digest": digest}

    records = []
    with ThreadPoolExecutor(max_workers=8) as pool:
        for index, item in enumerate(pool.map(fetch_one, prepared), start=1):
            name = f"pad_ufes_{index}"
            path = temp_dir / f"{name}.jpg"
            path.write_bytes(item["jpeg"])
            records.append(
                {
                    "name": name,
                    "group": item["group"],
                    "issue": item["issue"],
                    "label": item["group"],
                    "split": assigned[item["patient_id"]],
                    "source": "pad_ufes",
                    "original_name": item["img_id"],
                    "diagnostic": item["code"],
                    "patient_id": item["patient_id"],
                    "jpeg_path": path,
                    "width": item["width"],
                    "height": item["height"],
                    "md5": hashlib.md5(item["jpeg"]).hexdigest(),
                    "digest": item["digest"],
                }
            )
            if index % 100 == 0 or index == len(prepared):
                print(f"PAD-UFES-20 {index}/{len(prepared)}", flush=True)
    split_counts = Counter((item["group"], item["split"]) for item in records)
    if dict(split_counts) != PAD_SPLIT_COUNTS:
        raise SystemExit(f"PAD split counts {dict(split_counts)} do not match the published split")
    return records, [item["digest"] for item in records]


def fluo_entries(blob: bytes, start: int) -> list[dict]:
    signature = blob.rfind(b"PK\x05\x06")
    if signature < 0:
        raise SystemExit("could not read the FLUO-SC zip index")
    cd_size, cd_offset = struct.unpack_from("<II", blob, signature + 12)
    pos = cd_offset - start
    if pos < 0:
        raise SystemExit("FLUO-SC zip index is larger than the fetched tail")
    end = pos + cd_size
    entries = []
    while pos + 46 <= end and blob[pos : pos + 4] == b"PK\x01\x02":
        method = struct.unpack_from("<H", blob, pos + 10)[0]
        comp_size = struct.unpack_from("<I", blob, pos + 20)[0]
        name_len, extra_len, comment_len = struct.unpack_from("<HHH", blob, pos + 28)
        local_offset = struct.unpack_from("<I", blob, pos + 42)[0]
        name = blob[pos + 46 : pos + 46 + name_len].decode("utf-8", errors="replace")
        parts = [part for part in name.split("/") if part]
        folder = parts[-2] if len(parts) >= 2 else ""
        if folder in FLUO_FOLDERS and name.lower().endswith((".jpg", ".jpeg")):
            entries.append(
                {
                    "filename": parts[-1],
                    "issue": FLUO_FOLDERS[folder],
                    "method": method,
                    "comp_size": comp_size,
                    "local_offset": local_offset,
                }
            )
        pos += 46 + name_len + extra_len + comment_len
    return entries


def fetch_zip_entry(url: str, entry: dict) -> bytes:
    offset = entry["local_offset"]
    header = requests.get(url, headers={"Range": f"bytes={offset}-{offset + 511}"}, timeout=60)
    header.raise_for_status()
    raw = header.content
    if raw[:4] != b"PK\x03\x04":
        raise SystemExit(f"bad zip header for {entry['filename']}")
    name_len, extra_len = struct.unpack_from("<HH", raw, 26)
    data_start = offset + 30 + name_len + extra_len
    size = entry["comp_size"]
    payload = requests.get(
        url,
        headers={"Range": f"bytes={data_start}-{data_start + size - 1}"},
        timeout=120,
    )
    payload.raise_for_status()
    data = payload.content
    if entry["method"] == 8:
        data = zlib.decompress(data, -15)
    elif entry["method"] != 0:
        raise SystemExit(f"unsupported zip method {entry['method']} for {entry['filename']}")
    return data


def clinical_jpeg(raw: bytes) -> tuple[bytes, int, int, int]:
    with Image.open(io.BytesIO(raw)) as image:
        image = image.convert("RGB")
        width, height = image.size
        digest = average_hash(image)
        buffer = io.BytesIO()
        image.save(buffer, format="JPEG", quality=JPEG_QUALITY)
    return buffer.getvalue(), width, height, digest


def load_fluo(temp_dir: Path, pad_hashes: list[int]) -> tuple[list[dict], list[int]]:
    head = requests.head(FLUO_ZIP, allow_redirects=True, timeout=60)
    head.raise_for_status()
    size = int(head.headers["Content-Length"])
    entries = None
    for tail in (8_000_000, 64_000_000):
        start = max(0, size - tail)
        response = requests.get(head.url, headers={"Range": f"bytes={start}-{size - 1}"}, timeout=120)
        response.raise_for_status()
        try:
            entries = fluo_entries(response.content, start)
            break
        except SystemExit:
            entries = None
    if not entries:
        raise SystemExit("FLUO-SC clinical photos were not found in the zip")
    print(
        "FLUO-SC zip",
        {issue: sum(item["issue"] == issue for item in entries) for issue in FLUO_FOLDERS.values()},
    )

    def fetch_one(entry: dict) -> dict:
        encoded, width, height, digest = clinical_jpeg(fetch_zip_entry(head.url, entry))
        stem = Path(entry["filename"]).stem.lower()
        return {
            "name": f"fluo_{stem}",
            "issue": entry["issue"],
            "original_name": entry["filename"],
            "jpeg": encoded,
            "width": width,
            "height": height,
            "digest": digest,
        }

    kept = []
    skipped = Counter()
    with ThreadPoolExecutor(max_workers=6) as pool:
        downloaded = list(pool.map(fetch_one, entries))
    for item in downloaded:
        if too_close(item["digest"], pad_hashes):
            skipped[item["issue"]] += 1
            continue
        path = temp_dir / f"{item['name']}.jpg"
        path.write_bytes(item["jpeg"])
        with Image.open(path) as saved:
            saved_digest = average_hash(saved)
        kept.append(
            {
                "name": item["name"],
                "group": "Suspicious",
                "issue": item["issue"],
                "label": "Suspicious",
                "split": "train",
                "source": "fluo",
                "original_name": item["original_name"],
                "diagnostic": item["issue"],
                "patient_id": "",
                "jpeg_path": path,
                "width": item["width"],
                "height": item["height"],
                "md5": hashlib.md5(item["jpeg"]).hexdigest(),
                "digest": saved_digest,
            }
        )
    kept_counts = Counter(item["issue"] for item in kept)
    print("FLUO-SC kept", dict(kept_counts), "skipped", dict(skipped))
    if dict(kept_counts) != FLUO_KEPT:
        raise SystemExit(f"FLUO-SC kept {dict(kept_counts)}, expected {FLUO_KEPT}")
    kept.sort(key=lambda item: item["name"])
    return kept, [item["digest"] for item in kept]


def hiba_clinical_records() -> list[dict]:
    url = HIBA_SEARCH
    params = {"collections": 251, "limit": 100}
    records = []
    while url:
        response = requests.get(url, params=params, timeout=60)
        response.raise_for_status()
        payload = response.json()
        records.extend(payload["results"])
        url = payload.get("next")
        params = None
    selected = []
    for record in records:
        image_type = (record["metadata"]["acquisition"].get("image_type") or "")
        if not image_type.lower().startswith("clinical"):
            continue
        if record.get("copyright_license") != "CC-BY":
            raise SystemExit(f"{record.get('isic_id')} license {record.get('copyright_license')}")
        if "Hospital Italiano" not in (record.get("attribution") or ""):
            raise SystemExit(f"{record.get('isic_id')} attribution changed")
        diagnosis = record["metadata"]["clinical"].get("diagnosis_3") or ""
        issue = HIBA_LABELS.get(diagnosis)
        if issue:
            selected.append((record, issue))
    return selected


def load_hiba(temp_dir: Path, existing_hashes: list[int]) -> list[dict]:
    selected = hiba_clinical_records()
    print("Hospital Italiano selected", dict(Counter(issue for _record, issue in selected)))

    def fetch_one(item: tuple[dict, str]) -> dict:
        record, issue = item
        raw = fetch_bytes(record["files"]["full"]["url"])
        encoded, width, height, digest = clinical_jpeg(raw)
        return {
            "isic_id": record["isic_id"],
            "issue": issue,
            "jpeg": encoded,
            "width": width,
            "height": height,
            "digest": digest,
        }

    kept = []
    skipped = Counter()
    with ThreadPoolExecutor(max_workers=8) as pool:
        downloaded = list(pool.map(fetch_one, selected))
    for item in downloaded:
        short_side = min(item["width"], item["height"])
        if short_side < 128 or too_close(item["digest"], existing_hashes):
            skipped[item["issue"]] += 1
            continue
        name = f"hiba_{item['isic_id'].lower()}"
        path = temp_dir / f"{name}.jpg"
        path.write_bytes(item["jpeg"])
        kept.append(
            {
                "name": name,
                "group": "Suspicious",
                "issue": item["issue"],
                "label": "Suspicious",
                "split": "train",
                "source": "hiba",
                "original_name": item["isic_id"],
                "diagnostic": item["issue"],
                "patient_id": "",
                "jpeg_path": path,
                "width": item["width"],
                "height": item["height"],
                "md5": hashlib.md5(item["jpeg"]).hexdigest(),
            }
        )
    kept_counts = Counter(item["issue"] for item in kept)
    print("Hospital Italiano kept", dict(kept_counts), "skipped", dict(skipped))
    if dict(kept_counts) != HIBA_KEPT:
        raise SystemExit(f"Hospital Italiano kept {dict(kept_counts)}, expected {HIBA_KEPT}")
    kept.sort(key=lambda item: item["name"])
    return kept


def session_block(record: dict, session_id: str, modified: int) -> str:
    folder = f"/Data/{record['group']}/{record['issue']}/{record['name']}"
    name = record["name"]
    shape = f"[{record['width']},{record['height']},3]"
    return f"""      <Session name="{name}" sessionId="{session_id}" originalSessionId="00000000-0000-0000-0000-000000000000" ownerLocked="False" labelTrack="label" dataTrack="image" tags="None">
        <DataFile shape="{shape}" samplerate="0" modified="{modified}">{folder}/{name}.jpg</DataFile>
        <SessionFile>{folder}/{name}.imsession</SessionFile>
        <LabelFile modified="{modified + 40000}">{folder}/{name}.labelxml</LabelFile>
        <Labels>
          <Label count="1" length="0">{record['label']}</Label>
        </Labels>
        <CustomColumnValues>
          <CustomColumnValue columnId="{COLUMN_ID}">{record['label']}</CustomColumnValue>
        </CustomColumnValues>
      </Session>
"""


def write_session(record: dict, data_root: Path) -> str:
    name = record["name"]
    session_id = str(uuid.uuid5(SESSION_NAMESPACE, name))
    dest = data_root / record["group"] / record["issue"] / name
    dest.mkdir(parents=True)
    shutil.copy2(record["jpeg_path"], dest / f"{name}.jpg")
    (dest / f"{name}.labelxml").write_text(LABELXML.format(label=record["label"]), encoding="utf-8")
    (dest / f"{name}.imsession").write_text(
        IMSESSION.format(session_id=session_id, name=name),
        encoding="utf-8",
    )
    return session_block(record, session_id, filetime_ticks(dest / f"{name}.jpg"))


def write_improj(path: Path, blocks: dict[str, list[str]]) -> None:
    total = sum(len(items) for items in blocks.values())
    parts = [IMPROJ_HEADER]
    for split in ("train", "validation", "test"):
        target = f"{len(blocks[split]) / total:.4f}"
        parts.append(f'    <DataSet id="{split}" targetSize="{target}" labels="Complete">\n')
        parts.extend(blocks[split])
        parts.append("    </DataSet>\n")
    parts.append(IMPROJ_FOOTER)
    path.write_text("".join(parts), encoding="utf-8")


def write_mapping(path: Path, records: list[dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fieldnames = [
        "current_path",
        "current_name",
        "group",
        "issue",
        "original_name",
        "diagnostic",
        "label",
        "split",
        "patient_id",
        "source",
        "md5",
    ]
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames)
        writer.writeheader()
        for record in records:
            name = record["name"]
            writer.writerow(
                {
                    "current_path": f"Data/{record['group']}/{record['issue']}/{name}/{name}.jpg",
                    "current_name": f"{name}.jpg",
                    "group": record["group"],
                    "issue": record["issue"],
                    "original_name": record["original_name"],
                    "diagnostic": record["diagnostic"],
                    "label": record["label"],
                    "split": record["split"],
                    "patient_id": record["patient_id"],
                    "source": record["source"],
                    "md5": record["md5"],
                }
            )


def main() -> None:
    if DEST_DATA.exists() or DEST_IMPROJ.exists():
        raise SystemExit("Data/ or SkinLesionClassification.improj already exists")
    if STAGING.exists():
        shutil.rmtree(STAGING)
    staging_data = STAGING / "Data"
    staging_data.mkdir(parents=True)
    temp_dir = STAGING / "downloads"
    temp_dir.mkdir()
    try:
        pad_records, pad_hashes = load_pad(temp_dir)
        fluo_records, fluo_hashes = load_fluo(temp_dir, pad_hashes)
        hiba_records = load_hiba(temp_dir, pad_hashes + fluo_hashes)
        ordered = {
            "train": [item for item in pad_records if item["split"] == "train"] + fluo_records + hiba_records,
            "validation": [item for item in pad_records if item["split"] == "validation"],
            "test": [item for item in pad_records if item["split"] == "test"],
        }
        if [len(ordered[split]) for split in ("train", "validation", "test")] != [1716, 457, 444]:
            raise SystemExit(
                "session counts are "
                + ", ".join(f"{split} {len(ordered[split])}" for split in ordered)
            )
        names = [record["name"] for records in ordered.values() for record in records]
        if len(names) != len(set(names)):
            raise SystemExit("duplicate session name")
        blocks = {split: [] for split in ordered}
        mapping_rows = []
        for split, records in ordered.items():
            for record in records:
                blocks[split].append(write_session(record, staging_data))
                mapping_rows.append(record)
        write_improj(STAGING / DEST_IMPROJ.name, blocks)
        write_mapping(STAGING / DEST_MAPPING.name, mapping_rows)
        shutil.move(str(staging_data), str(DEST_DATA))
        DEST_MAPPING.parent.mkdir(parents=True, exist_ok=True)
        shutil.move(str(STAGING / DEST_IMPROJ.name), str(DEST_IMPROJ))
        shutil.move(str(STAGING / DEST_MAPPING.name), str(DEST_MAPPING))
        print(f"sessions {len(names)}")
        print(
            "train",
            len(ordered["train"]),
            "validation",
            len(ordered["validation"]),
            "test",
            len(ordered["test"]),
        )
    finally:
        if STAGING.exists() and not DEST_DATA.exists():
            shutil.rmtree(STAGING)
        elif STAGING.exists() and DEST_IMPROJ.exists() and DEST_MAPPING.exists():
            shutil.rmtree(STAGING)


if __name__ == "__main__":
    main()
