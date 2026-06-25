from __future__ import annotations

import argparse
import json
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Iterable


IMAGE_EXTENSIONS = (".jpg", ".jpeg", ".png", ".bmp", ".webp")
PREFIX_MAP = {
    "golf-ball-public": "gb",
    "infineon-public": "if",
}


@dataclass(frozen=True)
class SessionRename:
    dataset: str
    parent_dir: str
    old_name: str
    new_name: str
    image_ext: str


class RenameError(RuntimeError):
    pass


def detect_image_extension(session_dir: Path, basename: str) -> str:
    for ext in IMAGE_EXTENSIONS:
        if (session_dir / f"{basename}{ext}").exists():
            return ext

    candidates = [p.suffix.lower() for p in session_dir.iterdir() if p.is_file() and p.suffix.lower() in IMAGE_EXTENSIONS]
    if len(candidates) == 1:
        return candidates[0]

    raise RenameError(f"Could not uniquely determine image extension in {session_dir}")


def collect_session_renames(data_root: Path) -> list[SessionRename]:
    renames: list[SessionRename] = []

    for dataset_dir in sorted([p for p in data_root.iterdir() if p.is_dir()], key=lambda p: p.name):
        dataset_name = dataset_dir.name
        prefix = PREFIX_MAP.get(dataset_name)
        if not prefix:
            raise RenameError(f"No naming prefix configured for dataset '{dataset_name}'")

        session_dirs = sorted([p for p in dataset_dir.iterdir() if p.is_dir()], key=lambda p: p.name)
        for idx, session_dir in enumerate(session_dirs, start=1):
            old_name = session_dir.name
            image_ext = detect_image_extension(session_dir, old_name)

            expected_files = [
                session_dir / f"{old_name}.imsession",
                session_dir / f"{old_name}.labelxml",
                session_dir / f"{old_name}{image_ext}",
            ]
            missing = [str(p) for p in expected_files if not p.exists()]
            if missing:
                raise RenameError(f"Session '{old_name}' is missing expected files: {missing}")

            new_name = f"{prefix}_{idx:04d}"
            renames.append(
                SessionRename(
                    dataset=dataset_name,
                    parent_dir=str(dataset_dir),
                    old_name=old_name,
                    new_name=new_name,
                    image_ext=image_ext,
                )
            )

    ensure_unique_targets(renames)
    return renames


def ensure_unique_targets(renames: Iterable[SessionRename]) -> None:
    seen: set[tuple[str, str]] = set()
    for rename in renames:
        key = (rename.parent_dir, rename.new_name)
        if key in seen:
            raise RenameError(f"Duplicate target detected: {key}")
        seen.add(key)


def replace_text(path: Path, replacements: list[tuple[str, str]]) -> bool:
    original = path.read_text(encoding="utf-8")
    updated = original
    for old, new in replacements:
        updated = updated.replace(old, new)

    if updated != original:
        path.write_text(updated, encoding="utf-8")
        return True
    return False


def update_data_sessions(renames: list[SessionRename], dry_run: bool) -> None:
    for rename in renames:
        parent_dir = Path(rename.parent_dir)
        session_dir = parent_dir / rename.old_name

        imsession_path = session_dir / f"{rename.old_name}.imsession"
        if dry_run:
            pass
        else:
            replace_text(
                imsession_path,
                [
                    (f"{rename.old_name}{rename.image_ext}", f"{rename.new_name}{rename.image_ext}"),
                    (f"{rename.old_name}.labelxml", f"{rename.new_name}.labelxml"),
                ],
            )

        source_image = session_dir / f"{rename.old_name}{rename.image_ext}"
        source_imsession = session_dir / f"{rename.old_name}.imsession"
        source_label = session_dir / f"{rename.old_name}.labelxml"

        target_image = session_dir / f"{rename.new_name}{rename.image_ext}"
        target_imsession = session_dir / f"{rename.new_name}.imsession"
        target_label = session_dir / f"{rename.new_name}.labelxml"

        if not dry_run:
            source_image.rename(target_image)
            source_imsession.rename(target_imsession)
            source_label.rename(target_label)

            final_dir = parent_dir / rename.new_name
            if final_dir.exists():
                raise RenameError(f"Target directory already exists: {final_dir}")
            session_dir.rename(final_dir)


def update_project_file(project_file: Path, renames: list[SessionRename], dry_run: bool) -> None:
    replacements: list[tuple[str, str]] = []
    for rename in renames:
        replacements.append((f'name="{rename.old_name}"', f'name="{rename.new_name}"'))
        replacements.append((f"/{rename.old_name}/{rename.old_name}{rename.image_ext}", f"/{rename.new_name}/{rename.new_name}{rename.image_ext}"))
        replacements.append((f"/{rename.old_name}/{rename.old_name}.imsession", f"/{rename.new_name}/{rename.new_name}.imsession"))
        replacements.append((f"/{rename.old_name}/{rename.old_name}.labelxml", f"/{rename.new_name}/{rename.new_name}.labelxml"))

    if not dry_run:
        replace_text(project_file, replacements)


def update_predictions(models_root: Path, renames: list[SessionRename], dry_run: bool) -> None:
    mapping = {r.old_name: r for r in renames}

    prediction_roots = [p / "Predictions" for p in models_root.iterdir() if p.is_dir() and (p / "Predictions").is_dir()]
    for pred_root in prediction_roots:
        for old_name, rename in mapping.items():
            old_dir = pred_root / old_name
            if not old_dir.exists():
                continue

            pred_label = old_dir / "yolov5n-legacy-size320-batch16-epoch300_predictions.labelxml"
            pred_imsession_old = old_dir / f"{old_name}.imsession"
            pred_imsession_new = old_dir / f"{rename.new_name}.imsession"

            if not dry_run and pred_label.exists():
                replace_text(pred_label, [(f"{old_name}{rename.image_ext}", f"{rename.new_name}{rename.image_ext}")])

            if not dry_run and pred_imsession_old.exists():
                pred_imsession_old.rename(pred_imsession_new)

            new_dir = pred_root / rename.new_name
            if not dry_run:
                if new_dir.exists():
                    raise RenameError(f"Prediction target directory already exists: {new_dir}")
                old_dir.rename(new_dir)


def main() -> None:
    parser = argparse.ArgumentParser(description="Rename long session names to short names and update project/model references.")
    parser.add_argument("--root", type=Path, default=Path.cwd(), help="Project root path")
    parser.add_argument("--dry-run", action="store_true", help="Calculate and validate changes without writing")
    parser.add_argument("--map-file", type=Path, default=None, help="Optional path to write the old->new mapping as JSON")
    args = parser.parse_args()

    root = args.root.resolve()
    data_root = root / "Data"
    models_root = root / "Models"
    project_file = root / "GolfBallDetectionDemo.improj"

    if not data_root.is_dir():
        raise RenameError(f"Data directory not found: {data_root}")
    if not models_root.is_dir():
        raise RenameError(f"Models directory not found: {models_root}")
    if not project_file.is_file():
        raise RenameError(f"Project file not found: {project_file}")

    renames = collect_session_renames(data_root)

    if args.map_file:
        map_file = args.map_file.resolve()
        map_file.parent.mkdir(parents=True, exist_ok=True)
        map_file.write_text(json.dumps([asdict(r) for r in renames], indent=2), encoding="utf-8")

    print(f"Planned renames: {len(renames)}")
    if args.dry_run:
        print("Dry run mode: no files will be modified")

    update_project_file(project_file, renames, args.dry_run)
    update_data_sessions(renames, args.dry_run)
    update_predictions(models_root, renames, args.dry_run)

    print("Done")


if __name__ == "__main__":
    main()
