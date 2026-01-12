import argparse
import json
import os
import subprocess
from pathlib import Path
import requests

STUDIO_TEMPLATES_DIR = '_studio_templates'
TOKEN = os.getenv('STARTER_MODELS_PIPELINE_TOKEN')
PR_HEAD = os.getenv('PR_HEAD', None)

def start_pipeline(owner: str, branch: str) -> None:
    print('Collect all projects that have changes')
    if PR_HEAD:
        git_diff_range = f'origin/master...{branch}'
    else:
        git_diff_range = 'HEAD~1'
    changed_files = subprocess.run(
        ['git', 'diff', '--name-only', git_diff_range],
        capture_output=True,
        text=True,
        check=True
    ).stdout.splitlines()
    for file in changed_files:
        file_path = Path(file)
        is_template = False
        project_name = file_path.parts[0]
        if project_name == STUDIO_TEMPLATES_DIR:
            is_template = True
            project_name = file_path.parts[1]
        if project_name != file_path.name and not project_name.startswith('.') and not project_name.startswith('_'):
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
                                'repo_owner': owner,
                                'branch': branch,
                                'project_name': project_name,
                                'is_template': is_template,
                            }),
                        },
                    ],
                },
            )
            response.raise_for_status()
            print(f'Pipeline started successfully for {project_name}')


def main():
    if PR_HEAD:
        default_owner, _, default_branch = PR_HEAD.partition(':')
    else:
        default_owner = 'Infineon'
        default_branch = 'main'
    parser = argparse.ArgumentParser(
        description='Start pipeline for changed projects in the repository'
    )
    parser.add_argument(
        '--owner',
        help='Repository owner',
        default=default_owner,
    )
    parser.add_argument(
        '--branch',
        help='Branch name to compare for changes',
        default=default_branch,
    )
    start_pipeline(**vars(parser.parse_args()))


if __name__ == '__main__':
    main()
