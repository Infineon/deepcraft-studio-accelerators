#!/usr/bin/env python3
"""
Confusion Matrix Image Contribution Analyzer

This script takes a confusion matrix contributions JSON file and a Project.improj file,
matches session IDs with image paths from the project file, and generates a Markdown report
with clickable image links.

Usage:
    python analyze_cm_contributions.py --project /path/to/Project.improj --contributions train_cm_image_contributions.json

Output:
    - Markdown report with clickable image links showing which images contributed to each CM cell
"""

import argparse
import json
import os
import xml.etree.ElementTree as ET
from collections import defaultdict
from pathlib import Path
from urllib.parse import quote


def load_project_imdb(project_path: str) -> dict:
    """
    Load imdb structure from Project.improj file and build a session_id -> image_path mapping.

    Returns:
        dict: Mapping of session_id to session info including full image path
    """
    tree = ET.parse(project_path)
    root = tree.getroot()

    session_map = {}
    database_dir = os.path.dirname(os.path.abspath(project_path))
    print(f"Project file directory: {database_dir}")

    database = root.find('.//Database')
    if database is None:
        raise ValueError("No Database element found in project file")
    print(f"Count of database.findall('DataSet') = {len(database.findall('DataSet'))}")
    for dataset in database.findall('DataSet'):
        dataset_id = dataset.attrib.get('id', 'unknown')
        print(f"Processing dataset: {dataset_id}")
        sessions = dataset.findall('Session') + dataset.findall('Segment')
        print(f"Found {len(sessions)} sessions in dataset: {dataset_id}")
        for session in sessions:
            print(f"Processing session: {session.attrib.get('name', 'unknown')} (ID: {session.attrib.get('sessionId', 'unknown')}) in dataset: {dataset_id}")
            try:
                session_name = session.attrib.get('name', '').strip().strip('"').strip("'")
                session_id = session.attrib.get('sessionId', '')

                data_file_elem = session.find('DataFile')
                data_file_relative = data_file_elem.text.strip().strip('"').strip("'").lstrip('/') if data_file_elem is not None else ''
                data_file_name = os.path.basename(data_file_relative)

                data_file_path = os.path.abspath(os.path.join(
                    database_dir, data_file_relative
                ))

                if session_id:
                    session_map[session_id] = {
                        "path": data_file_path,
                        "name": session_name,
                        "dataset": dataset_id,
                        "filename": data_file_name
                    }
            except Exception as e:
                print(f"Warning: Could not parse session: {e}")
                continue

    return session_map


def load_contributions(contributions_path: str) -> dict:
    """Load the contribution JSON file."""
    with open(contributions_path, 'r') as f:
        return json.load(f)


def make_relative_link(target_path: str, from_file: str) -> str:
    """Create a relative path from from_file's directory to target_path, using forward slashes for Markdown compatibility."""
    from_dir = os.path.dirname(os.path.abspath(from_file))
    rel = os.path.relpath(os.path.abspath(target_path), from_dir)
    return quote(rel.replace('\\', '/'), safe='/')


def generate_markdown_report(contributions: dict, output_path: str, session_map: dict):
    """
    Generate a Markdown report from contributions data with clickable image links.
    Only creates links for images found in the project file.
    """

    lines = [
        "# Confusion Matrix Image Contribution Report",
        "",
        f"**Task:** {contributions.get('task', 'detect')}",
        f"**Number of Classes:** {contributions.get('num_classes', 0)}",
        f"**Sessions in Project File:** {len(session_map)}",
        "",
        "---",
        "",
        "## Summary",
        "",
    ]

    contrib_data = contributions.get("contributions", {})

    lines.append("| Cell | Predicted | True | Count | Sessions Matched |")
    lines.append("|------|-----------|------|-------|------------------|")

    total_contributions = 0
    total_matched_sessions = set()
    total_unmatched = 0

    for cell_key, cell_data in sorted(contrib_data.items()):
        pred_name = cell_data.get("predicted_class_name", "?")
        true_name = cell_data.get("true_class_name", "?")
        count = cell_data.get("count", 0)

        images = cell_data.get("images", [])
        matched_count = 0
        for img in images:
            if isinstance(img, dict):
                sid = img.get("session_id", "")
                if sid and sid in session_map:
                    matched_count += 1
                    total_matched_sessions.add(sid)

        total_contributions += count
        total_unmatched += (len(images) - matched_count)

        lines.append(f"| {cell_key} | {pred_name} | {true_name} | {count} | {matched_count} |")

    lines.append("")
    lines.append(f"**Total Contributions:** {total_contributions}")
    lines.append(f"**Sessions Matched to Project:** {len(total_matched_sessions)}")
    if total_unmatched > 0:
        lines.append(f"**Unmatched Entries:** {total_unmatched} (session IDs not found in project file)")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("## Detailed Contributions")
    lines.append("")

    for cell_key, cell_data in sorted(contrib_data.items()):
        pred_name = cell_data.get("predicted_class_name", "?")
        true_name = cell_data.get("true_class_name", "?")
        pred_class = cell_data.get("predicted_class", "?")
        true_class = cell_data.get("true_class", "?")
        images = cell_data.get("images", [])
        count = cell_data.get("count", 0)

        if pred_class == true_class:
            cell_type = "True Positive (TP)" if pred_name != "background" else "True Negative (TN)"
        elif pred_name == "background":
            cell_type = "False Negative (FN)"
        elif true_name == "background":
            cell_type = "False Positive (FP)"
        else:
            cell_type = "Misclassification"

        lines.append(f"### {pred_name} (predicted) vs {true_name} (true)")
        lines.append(f"**Type:** {cell_type}")
        lines.append("")

        if not images:
            lines.append("*No images contributed to this cell.*")
            lines.append("")
            continue

        matched_sessions = {}
        unmatched_count = 0

        for img in images:
            if isinstance(img, dict):
                session_id = img.get("session_id", "")
                if session_id and session_id in session_map:
                    if session_id not in matched_sessions:
                        matched_sessions[session_id] = []
                    matched_sessions[session_id].append(img)
                else:
                    unmatched_count += 1

        lines.append(f"**Total contributions:** {count}")
        lines.append(f"**Sessions with images:** {len(matched_sessions)}")
        if unmatched_count > 0:
            lines.append(f"**Unmatched entries:** {unmatched_count}")
        lines.append("")

        if not matched_sessions:
            lines.append("*No sessions matched in project file.*")
            lines.append("")
            continue

        lines.append("| Session Name | Dataset | Count | Image |")
        lines.append("|--------------|---------|-------|-------|")

        for session_id, session_images in sorted(matched_sessions.items(), key=lambda x: -len(x[1])):
            img_info = session_map[session_id]
            img_path = img_info["path"]
            img_filename = img_info["filename"]
            session_name = img_info["name"]
            dataset = img_info["dataset"]
            contrib_count = len(session_images)

            rel_link = make_relative_link(img_path, output_path)
            image_link = f"[{img_filename}]({rel_link})"

            lines.append(f"| {session_name} | {dataset} | {contrib_count} | {image_link} |")

        lines.append("")

        if len(matched_sessions) > 0:
            lines.append("<details>")
            lines.append("<summary>All image paths (click to expand)</summary>")
            lines.append("")
            lines.append("| # | Session Name | Image Path | Link |")
            lines.append("|---|--------------|------------|------|")

            idx = 1
            for session_id in sorted(matched_sessions.keys()):
                img_info = session_map[session_id]
                path = img_info["path"]
                session_name = img_info["name"]
                rel_link = make_relative_link(path, output_path)

                display_path = "..." + path[-50:] if len(path) > 53 else path

                lines.append(f"| {idx} | {session_name} | `{display_path}` | [Open]({rel_link}) |")
                idx += 1

            lines.append("")
            lines.append("</details>")
            lines.append("")

    lines.append("---")
    lines.append("")
    lines.append("## How to Use This Report")
    lines.append("")
    lines.append("1. **Click on image links** to open the corresponding image in your default viewer")
    lines.append("2. **Expand details sections** to see all image paths for each confusion matrix cell")
    lines.append("3. **Focus on error cells** (FP, FN, Misclassifications) to understand model weaknesses")
    lines.append("")
    lines.append("> **Note:** Image links are relative paths from this report file to the project's Data folder.")
    lines.append("")

    with open(output_path, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines))

    print(f"Markdown report saved to: {output_path}")
    print(f"   - Total cells: {len(contrib_data)}")
    print(f"   - Total contributions: {total_contributions}")
    print(f"   - Sessions matched: {len(total_matched_sessions)}")

    return output_path


def main():
    parser = argparse.ArgumentParser(
        description="Generate Markdown report from confusion matrix image contributions with clickable image links"
    )
    parser.add_argument(
        "--project", "-p",
        required=True,
        help="Path to Project.improj file (required for matching session IDs to image paths)"
    )
    parser.add_argument(
        "--contributions", "-c",
        required=True,
        help="Path to confusion matrix contributions JSON file"
    )
    parser.add_argument(
        "--output", "-o",
        default=None,
        help="Output path for Markdown report (default: same dir as contributions with _report.md suffix)"
    )

    args = parser.parse_args()

    if not os.path.exists(args.project):
        print(f"Error: Project file not found: {args.project}")
        return 1

    if not os.path.exists(args.contributions):
        print(f"Error: Contributions file not found: {args.contributions}")
        return 1

    if args.output:
        output_path = args.output
    else:
        base_name = os.path.splitext(os.path.basename(args.contributions))[0]
        output_dir = os.path.dirname(args.contributions) or "."
        output_path = os.path.join(output_dir, f"{base_name}_report.md")

    print(f"Loading project file: {args.project}")
    try:
        session_map = load_project_imdb(args.project)
        print(f"   Found {len(session_map)} sessions in project")
    except Exception as e:
        print(f"Error loading project file: {e}")
        return 1

    print(f"Loading contributions: {args.contributions}")
    try:
        contributions = load_contributions(args.contributions)
    except Exception as e:
        print(f"Error loading contributions file: {e}")
        return 1

    print(f"Generating Markdown report...")
    try:
        generate_markdown_report(contributions, output_path, session_map)
    except Exception as e:
        print(f"Error generating report: {e}")
        return 1

    print("\nDone!")
    return 0


if __name__ == "__main__":
    exit(main())
