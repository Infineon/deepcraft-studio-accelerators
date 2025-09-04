import json
import os
import requests

token = os.environ['STARTER_MODELS_PIPELINE_TOKEN']
if not token:
    raise Exception('Token is missing')
user, _, branch = os.environ['PR_HEAD'].partition(':')
response = requests.post(
    url='https://api.bitbucket.org/2.0/repositories/Imagimob/_starter-projects-pipeline/pipelines',
    headers={
        'Authorization': f'Bearer {token}',
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
                    'repo_owner': user,
                    'branch': branch,
                }),
            },
        ],
    },
)
response.raise_for_status()
