import argparse, sys
from autogit.loop import init_autogit
from autogit.utils import is_git_installed, perror, is_git_repo
def __arg_parser__():
    parser = argparse.ArgumentParser()
    parser.description = "A simple cli tool for automating basic git jobs"
    parser.add_argument("-i","--commit-interval", metavar="<seconds>", type=int, help="Set interval after which you want to add auto commit (default = 10s)")
    parser.add_argument("-t","-p","--push-interval",metavar="<seconds>", type=int, help="Interval for remote push.")
    parser.add_argument("-r","--push", "--auto-push",action='store_true', help="Specify to run commit and push together; -p or -t must me specified. Or use --poi <seconds> for all together")
    parser.add_argument("--poi", "--push-only-interval", metavar="<seconds>", type=int, help="Specify to run commit and push together and pass their interval")

    args = parser.parse_args()

    if  len(sys.argv) == 1:
        perror("autogit: no arguments provided")
        print("please use -h or --help for listing available arguments")
        exit(1)
    commit_interval:int = args.commit_interval
    push_interval:int = args.push_interval or args.poi
    push_only: bool = args.push or args.poi != None
    
    
    
    if push_only:
        if not push_interval:
            perror("autogit: fatal error: please specify push-only interval using -t or -p or use --poi <seconds> instead of -r")
            exit(122)
        elif push_interval < 10:
            perror("autogit: push interval cannot be less than 10 seconds")

    autogit_props :dict = {
        "commit_interval": commit_interval,
        "push_interval": push_interval,
        "push_only": push_only
    }

    if is_git_installed:
    
        if is_git_repo():
            try:
                init_autogit(autogit_props=autogit_props)
            except KeyboardInterrupt:
                sys.stdout.write("\033[?25h")  # Enable cursor blinking and show cursor
                print("\nScript interrupted. Cleaning up...")
        else:
            perror("autogit: fatal error, not a git repository; make sure to run git init ")
            sys.exit(10)
    else:
        perror("autogit: couldn't find git in your $PATH . please install git")