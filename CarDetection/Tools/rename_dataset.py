#!/usr/bin/env python3
"""Rename COCO dataset image files to short, progressive names and fix annotations.

Run this from the dataset root folder (the folder that contains the
``train``/``valid``/``test`` split folders, each holding an
``_annotations.coco.json`` file).

Example
-------
    python rename_dataset.py img

This renames the images in every split to ``img001.jpg``, ``img002.jpg`` ... and
updates the ``file_name`` field of every image entry in the corresponding
``_annotations.coco.json`` so the annotations stay valid.

A single counter runs continuously across all splits, so every image gets a
unique name (e.g. train ends at ``img800`` and valid starts at ``img801``). Use
``--per-split`` to instead restart numbering from 1 in each split folder.
"""

from __future__ import annotations

import argparse
import json
import os
import sys

ANNOTATION_FILE = "_annotations.coco.json"
# Common image extensions found in COCO exports.
IMAGE_EXTENSIONS = {".jpg", ".jpeg", ".png", ".bmp", ".gif", ".tif", ".tiff", ".webp"}


def find_split_dirs(root: str) -> list[str]:
    """Return the sub-folders of *root* that contain a COCO annotation file."""
    splits = []
    for entry in sorted(os.listdir(root)):
        path = os.path.join(root, entry)
        if os.path.isdir(path) and os.path.isfile(os.path.join(path, ANNOTATION_FILE)):
            splits.append(path)
    return splits


def rename_split(split_dir: str, prefix: str, start: int, pad: int, dry_run: bool) -> int:
    """Rename all images in *split_dir* and rewrite its annotation file.

    Returns the next number to use (useful for continuous numbering).
    """
    annotation_path = os.path.join(split_dir, ANNOTATION_FILE)
    with open(annotation_path, "r", encoding="utf-8") as fh:
        data = json.load(fh)

    images = data.get("images", [])
    if not images:
        print(f"  [skip] no images listed in {annotation_path}")
        return start

    # Keep a stable, reproducible order based on the existing image id.
    images_sorted = sorted(images, key=lambda img: img["id"])

    # Build the old -> new name mapping first so we can detect collisions.
    mapping: dict[str, str] = {}
    used_new_names: set[str] = set()
    number = start
    for img in images_sorted:
        old_name = img["file_name"]
        ext = os.path.splitext(old_name)[1].lower() or ".jpg"
        new_name = f"{prefix}{number:0{pad}d}{ext}"
        if new_name in used_new_names:
            raise RuntimeError(f"Duplicate target name generated: {new_name}")
        mapping[old_name] = new_name
        used_new_names.add(new_name)
        number += 1

    # Rename the actual files via a temporary name to avoid clobbering any
    # existing file whose name collides with a target name.
    for old_name, new_name in mapping.items():
        old_path = os.path.join(split_dir, old_name)
        if not os.path.isfile(old_path):
            print(f"  [warn] file missing on disk, annotation only: {old_name}")
            continue
        tmp_path = old_path + ".rntmp"
        if dry_run:
            print(f"  {old_name} -> {new_name}")
            continue
        os.rename(old_path, tmp_path)

    if not dry_run:
        for old_name, new_name in mapping.items():
            tmp_path = os.path.join(split_dir, old_name + ".rntmp")
            new_path = os.path.join(split_dir, new_name)
            if os.path.isfile(tmp_path):
                os.rename(tmp_path, new_path)

    # Update the annotation entries in place.
    for img in images:
        old_name = img["file_name"]
        if old_name in mapping:
            img["file_name"] = mapping[old_name]
            extra = img.get("extra")
            if isinstance(extra, dict) and "name" in extra:
                extra["name"] = mapping[old_name]

    if not dry_run:
        with open(annotation_path, "w", encoding="utf-8") as fh:
            json.dump(data, fh)

    print(f"  renamed {len(mapping)} images in '{os.path.basename(split_dir)}'")
    return number


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("prefix", help="Prefix for the new file names, e.g. 'img'.")
    parser.add_argument("--root", default=".",
                        help="Dataset root folder (default: current directory).")
    parser.add_argument("--per-split", action="store_true",
                        help="Restart numbering from 1 in each split folder. By "
                             "default a single counter runs across all splits so "
                             "every image name is unique.")
    parser.add_argument("--dry-run", action="store_true",
                        help="Show what would be renamed without changing anything.")
    args = parser.parse_args(argv)

    root = os.path.abspath(args.root)
    splits = find_split_dirs(root)
    if not splits:
        print(f"No split folders with '{ANNOTATION_FILE}' found under {root}.")
        return 1

    print(f"Dataset root: {root}")
    if args.dry_run:
        print("(dry run - no files will be changed)\n")

    # Determine a single zero-padding width based on the total image count so
    # names sort correctly and stay consistent across every split.
    total_images = 0
    for split_dir in splits:
        with open(os.path.join(split_dir, ANNOTATION_FILE), "r", encoding="utf-8") as fh:
            total_images += len(json.load(fh).get("images", []))
    pad = max(3, len(str(total_images)))

    number = 1
    for split_dir in splits:
        print(f"Processing '{os.path.basename(split_dir)}'...")
        start = 1 if args.per_split else number
        next_number = rename_split(split_dir, args.prefix, start, pad, args.dry_run)
        if not args.per_split:
            number = next_number

    print("Done.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
