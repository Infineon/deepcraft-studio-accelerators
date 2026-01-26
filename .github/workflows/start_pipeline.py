import argparse
import json
import os
import subprocess
from pathlib import Path

import requests

STUDIO_TEMPLATES_DIR = '_studio_templates'
TOKEN = os.environ['STARTER_MODELS_PIPELINE_TOKEN']

def start_pipeline(pr_number: str = '') -> None:
    print('Collect all projects that have changes')
    if pr_number:
        git_diff_range = 'origin/main'
    else:
        git_diff_range = 'HEAD~1'
    changed_files = subprocess.run(
        ['git', 'diff', '--name-only', git_diff_range],
        capture_output=True,
        text=True,
        check=True
    ).stdout.splitlines()
    changed_projects = set()
    for file in changed_files:
        file_path = Path(file)
        file_parts = file_path.parts
        is_template = STUDIO_TEMPLATES_DIR == file_parts[0]
        project_name = file_parts[1] if is_template else file_parts[0]
        if project_name != file_path.name and not project_name.startswith('.') and not project_name.startswith('_'):
            changed_projects.add((project_name, is_template))
    for project_name, is_template in changed_projects:
        response = requests.post(
            url='https://api.bitbucket.org/2.0/repositories/Imagimob/_starter-projects-pipeline/pipelines',
            headers={
                'Authorization': f'Bearer {TOKEN}',
                'Content-Type': 'application/json',
                'Accept': 'application/json',
            },
            json={
                'target': {
                    'type': 'pipeline_ref_target',
                    'ref_type': 'branch',
                    'ref_name': 'master',
                    'selector': {
                        'type': 'custom',
                        'pattern': 'update-project',
                    }
                },
                'variables': [
                    {
                        'key': 'PIPELINE',
                        'value': json.dumps({
                            'pr_number': pr_number,
                            'path': Path(STUDIO_TEMPLATES_DIR if is_template else '', project_name),
                        }),
                    },
                ],
            },
        )
        response.raise_for_status()
        print(f'Pipeline started successfully for {project_name}')


def main():
    parser = argparse.ArgumentParser(
        description='Start pipeline for changed projects in the repository'
    )
    parser.add_argument(
        '--pr-number',
        help='Pull request number',
    )
    start_pipeline(**vars(parser.parse_args()))


if __name__ == '__main__':
    main()
