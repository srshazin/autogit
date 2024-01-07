import sys, time
from autogit.utils import *
from autogit.processor import make_commit
def init_autogit(autogit_props:dict):
    MINIMUM_COMMIT_INTERVAL = 10
    commit_interval: int = autogit_props.get("commit_interval")
    push_interval: int = autogit_props.get("push_interval")
    agit_stats: dict[str, bool]= {
        "commit": False,
        "push": False 
    }
    if commit_interval < MINIMUM_COMMIT_INTERVAL:
        perror("autogit: commit interval cannot be less than 10 seconds")
        sys.exit(1)
    else:
        log_success(f'commit interval set to {commit_interval} seconds')
        agit_stats["commit"]  =True
    
    if push_interval:
        if push_interval > commit_interval:
            log_success(f"auto push enabled: interval {push_interval} seconds", False)
            agit_stats["push"] = True
        elif push_interval <= commit_interval:
            if push_interval < MINIMUM_COMMIT_INTERVAL:
                perror("autogit: push interval cannot be less than 10 seconds")
                sys.exit(1)
            else:
                print(get_yellow_str("push interval is <= commit interval, auto commit disabled"))
                agit_stats["commit"]  = False
                agit_stats["push"] = True
        else: 
            perror("autogit: fatal error");
    loop(agit_stats=agit_stats, agit_props=autogit_props)


def loop(agit_stats: dict, agit_props:dict):
    if agit_stats["commit"] and not agit_stats["push"]:
        # mode: 1
        print(get_magenta_str("starting in mode: 1"))
        while True:
            mod_1(agit_props=agit_props)
    elif agit_stats["commit"] and  agit_stats["push"]:
        # mode 2
        print(get_blue_str("starting in mode: 2"))
        # mode 3
    elif not agit_stats["commit"] and  agit_stats["push"]:
        print(get_cyan_str("starting in mode: 3"))
        mod_3(agit_props=agit_props)

def mod_1(agit_props: dict):
    time.sleep(agit_props["commit_interval"])
    make_commit()

def mod_3(agit_props: dict):
    pass