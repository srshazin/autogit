import argparse
def __arg_parser__():
    parser = argparse.ArgumentParser()
    parser.description = "A simple cli tool for automating basic git jobs"
    parser.add_argument("-i","--commit-interval", metavar="seconds", help="Set interval after which you want to add auto commit (default = 10s)", required=False)
    parser.add_argument("-p","--push-interval", help="Interval for remote push. If not passed remote push will be disabled")

    args = parser.parse_args()