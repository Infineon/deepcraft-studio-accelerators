#     #!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import csv
import os
import sys
import tempfile
import shutil
import fnmatch


def process_file_if_header_matches(file_path: str) -> bool:
    """
    If the second column of the first row in a CSV (comma-separated values) file is named ‘Length’,
    delete the second column of all rows and save the file. Do nothing otherwise.
    - If a row has fewer than two columns, do not modify that row.
    - Write to a temporary file before replacing the original.
    Return value: True if modified, False if unchanged or failed.
    """
    tmp_path = None
    try:
        with open(file_path, mode='r', encoding='utf-8-sig', errors='replace', newline='') as rf:
            reader = csv.reader(rf, delimiter=',')
            first_row = next(reader, None)

            if not first_row or len(first_row) < 2:
                return False

            if first_row[1].strip() != 'Length':
                return False

            dir_name = os.path.dirname(file_path) or '.'
            with tempfile.NamedTemporaryFile(
                mode='w',
                encoding='utf-8',
                newline='',
                delete=False,
                dir=dir_name,
                prefix='.tmp_remove2col_',
                suffix='.csv'
            ) as wf:
                tmp_path = wf.name
                writer = csv.writer(wf, delimiter=',')

                # 1st line
                writer.writerow([first_row[0]] + first_row[2:] if len(first_row) >= 2 else first_row)

                # From the 2nd line onward
                for row in reader:
                    if len(row) >= 2:
                        writer.writerow([row[0]] + row[2:])
                    else:
                        writer.writerow(row)

        try:
            os.replace(tmp_path, file_path)
        except Exception:
            shutil.move(tmp_path, file_path)
        return True

    except Exception as e:
        print(f"Error: An exception occurred while processing {file_path}: {e}", file=sys.stderr)
        return False
    finally:
        if tmp_path and os.path.exists(tmp_path):
            try:
                os.remove(tmp_path)
            except Exception:
                pass


def name_matches(name: str, pattern: str) -> bool:
    """
    Determines whether a filename matches a pattern.
    - If the pattern contains *, ?, or [], uses fnmatch as a wildcard
    - Otherwise, determines partial match (whether pattern is contained within name)
    """
    if any(ch in pattern for ch in "*?[]"):
        return fnmatch.fnmatch(name, pattern)
    else:
        return pattern in name


def find_and_process(dir_path: str, pattern: str) -> tuple[int, int]:
    """
    Recursively search the specified directory and its subdirectories, opening files matching the pattern.
    Only when the first line and second column are ‘Length’, overwrite the file after deleting the second column.
    Return value: (number of modified files, total number of matching files)
    """
    changed = 0
    matched_total = 0
    for root, _, files in os.walk(dir_path):
        for name in files:
            if name_matches(name, pattern):
                matched_total += 1
                path = os.path.join(root, name)
                ok = process_file_if_header_matches(path)
                if ok:
                    changed += 1
                    print(f"Changed: {path}")
                else:
                    print(f"No changes (conditions not met or processing not possible): {path}")
    return changed, matched_total


def main():
    parser = argparse.ArgumentParser(
        description="Search for filenames using wildcards or partial matches within the specified directory. If the first row and second column contain ‘Length’, delete the second column of all rows and overwrite the file (CSV: comma-separated)."
    )
    parser.add_argument("directory", help="Path of the directory to start searching from")
    parser.add_argument("filename_pattern", help="Search filename patterns (e.g., *.csv or report)")
    args = parser.parse_args()

    dir_path = os.path.abspath(args.directory)
    if not os.path.isdir(dir_path):
        print(f"Error: Directory does not exist: {dir_path}", file=sys.stderr)
        sys.exit(1)

    # Patterns are compared by base name (directory components are ignored even if included)
    pattern = os.path.basename(args.filename_pattern)

    changed, matched_total = find_and_process(dir_path, pattern)
    if matched_total == 0:
        print("No matching files were found.")
        sys.exit(2)
    else:
        print(f"Out of {matched_total} matches, {changed} files were modified.")
        sys.exit(0)


if __name__ == "__main__":
    main()
