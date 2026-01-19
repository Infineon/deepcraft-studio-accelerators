import argparse
import json
import os
import subprocess
from pathlib import Path
import requests

STUDIO_TEMPLATES_DIR = '_studio_templates'
TOKEN = os.getenv('STARTER_MODELS_PIPELINE_TOKEN')

def start_pipeline(owner: str, repo: str, branch: str, is_pr: bool) -> None:
    print('Collect all projects that have changes')
    if is_pr:
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
        is_template = False
        project_name = file_path.parts[0]
        if project_name == STUDIO_TEMPLATES_DIR:
            is_template = True
            project_name = file_path.parts[1]
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
                    # TODO: Set ref_name back to main before merging
                    'ref_name': 'feature/SD-5322-move-templates-to-accelerators',
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
                            'repo_name': repo,
                            'branch': branch,
                            'project_name': project_name,
                            'root_path': STUDIO_TEMPLATES_DIR if is_template else '',
                            'is_pr': is_pr,
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
        '--owner',
        help='Repository owner',
    )
    parser.add_argument(
        '--repo',
        help='Repository name',
    )
    parser.add_argument(
        '--branch',
        help='Branch name to compare for changes',
    )
    parser.add_argument(
        '--is-pr',
        action='store_true',
        help='Whether this is a pull request',
    )
    start_pipeline(**vars(parser.parse_args()))


if __name__ == '__main__':
    main()
