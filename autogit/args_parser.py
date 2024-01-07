import argparse, sys
from autogit.loop import init_autogit
from autogit.utils import is_git_installed, perror, is_git_repo
def __arg_parser__():
    parser = argparse.ArgumentParser()
    parser.description = "A simple cli tool for automating basic git jobs"
    parser.add_argument("-i","--commit-interval", metavar="seconds", type=int, help="Set interval after which you want to add auto commit (default = 10s)", required=True)
    parser.add_argument("-p","--push-interval",metavar="seconds", type=int, help="Interval for remote push. If not passed remote push will be disabled")

    args = parser.parse_args()

    commit_interval = args.commit_interval
    push_interval = args.push_interval
    autogit_props :dict = {
        "commit_interval": commit_interval,
        "push_interval": push_interval
    }
    if is_git_installed:
    
        if is_git_repo():
            try:
                init_autogit(autogit_props=autogit_props)
            except KeyboardInterrupt:
                print("\nScript interrupted. Cleaning up...")
        else:
            perror("autogit: fatal error, not a git repository; make sure to run git init ")
            sys.exit(10)
    else:
        perror("autogit: couldn't find git in your $PATH . please install git")