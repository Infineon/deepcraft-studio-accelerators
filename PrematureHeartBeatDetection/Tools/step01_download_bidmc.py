"""Download PhysioNet BIDMC Congestive Heart Failure Database v1.0.0.

Writes ``chf01``–``chf15`` ``.hea``, ``.dat``, and ``.ecg`` under
``Raw_Data/chfdb``. The database license is ODC-By 1.0; cite it from the
project README. Prefers an unsigned S3 sync when ``aws`` is on PATH, then
fills any missing files over HTTPS.
"""

from __future__ import annotations

import urllib.request
from pathlib import Path

PHYSIONET_CHFDB = "https://physionet.org/files/chfdb/1.0.0/"
RECORDS = [f"chf{i:02d}" for i in range(1, 16)]
EXTENSIONS = (".hea", ".dat", ".ecg")


def _need(path: Path) -> bool:
    """True when the file is missing or empty and must be fetched."""
    return not path.is_file() or path.stat().st_size == 0


def _download_http(url: str, dest: Path, timeout: int = 60, retries: int = 4) -> None:
    """Fetch one file over HTTPS into ``dest`` through a ``.part`` temp file.

    Retries a few times and only renames to ``dest`` once the download is
    complete and non-empty, so an interrupted run leaves no half files.
    """
    dest.parent.mkdir(parents=True, exist_ok=True)
    tmp = dest.with_suffix(dest.suffix + ".part")
    last_err: Exception | None = None
    for attempt in range(1, retries + 1):
        print(f"Downloading {url} (attempt {attempt}/{retries})", flush=True)
        try:
            if tmp.exists():
                tmp.unlink()
            req = urllib.request.Request(
                url, headers={"User-Agent": "PrematureHeartBeatDetection/1.0"}
            )
            with urllib.request.urlopen(req, timeout=timeout) as resp, tmp.open("wb") as out:
                while True:
                    chunk = resp.read(1024 * 1024)
                    if not chunk:
                        break
                    out.write(chunk)
            if tmp.stat().st_size == 0:
                raise IOError(f"empty download: {url}")
            tmp.replace(dest)
            return
        except Exception as exc:
            last_err = exc
            print(f"  failed: {exc}", flush=True)
            if tmp.exists():
                tmp.unlink(missing_ok=True)
    raise RuntimeError(f"Could not download {url}: {last_err}") from last_err


def download_chfdb(dest: Path, *, force: bool = False, records: list[str] | None = None) -> Path:
    """Make sure every record's ``.hea``, ``.dat``, and ``.ecg`` is under ``dest``.

    Writes ``SOURCE.txt`` with the database URL and license. When ``aws`` is
    installed, syncs the public S3 mirror first (faster, no credentials);
    anything still missing is downloaded file by file over HTTPS. Existing
    complete files are reused unless ``force`` is set.
    """
    dest.mkdir(parents=True, exist_ok=True)
    recs = records or RECORDS
    (dest / "SOURCE.txt").write_text(
        "BIDMC Congestive Heart Failure Database v1.0.0\n"
        f"{PHYSIONET_CHFDB}\n"
        "License: Open Data Commons Attribution License v1.0\n",
        encoding="utf-8",
    )
    missing = [rec for rec in recs if force or any(_need(dest / f"{rec}{ext}") for ext in EXTENSIONS)]
    if missing:
        import shutil
        import subprocess

        aws = shutil.which("aws")
        if aws:
            print("Syncing chfdb from s3://physionet-open/chfdb/1.0.0/ ...", flush=True)
            subprocess.check_call(
                [
                    aws,
                    "s3",
                    "sync",
                    "--no-sign-request",
                    "s3://physionet-open/chfdb/1.0.0/",
                    str(dest),
                ]
            )
        missing = [rec for rec in recs if force or any(_need(dest / f"{rec}{ext}") for ext in EXTENSIONS)]
    for rec in recs:
        for ext in EXTENSIONS:
            out = dest / f"{rec}{ext}"
            if not force and not _need(out):
                print(f"Reusing {out.name}", flush=True)
                continue
            url = f"{PHYSIONET_CHFDB}{rec}{ext}"
            _download_http(url, out)
    return dest


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--dest",
        type=Path,
        default=Path(__file__).resolve().parent.parent / "Raw_Data" / "chfdb",
    )
    parser.add_argument("--force", action="store_true")
    parser.add_argument("--chf07-only", action="store_true")
    args = parser.parse_args()
    recs = ["chf07"] if args.chf07_only else None
    download_chfdb(args.dest, force=args.force, records=recs)
    print(f"Saved under {args.dest}")
