import sys
from autogit.utils import *
def init_autogit(autogit_props:dict):
    commit_interval: int = autogit_props.get("commit_interval")
    push_interval: int = autogit_props.get("push_interval")
    if commit_interval < 10:
        print("commit interval cannot be less than 10 seconds")
        sys.exit(1)
    else:
        log_success(f'commit interval set to {commit_interval} seconds')
    
    if push_interval:
        if push_interval > commit_interval:
            log_success("auto push enabled", True)