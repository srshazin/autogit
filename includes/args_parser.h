#include "autogit.h"
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

Autogit autogit_props;
int parse_args(int key, char *arg, struct argp_state *state) {

  switch (key) {
  case 'i': {
    autogit_props.commit_interval = atoi(arg);
  } break;
  case 'p': {
    autogit_props.push_interval = atoi(arg);
  }

  default:
    ARGP_ERR_UNKNOWN;
  }
  return 0;
}

struct argp_option options[] = {
    {"interval", 'i', "seconds", 0,
     "Set interval after which you want to add auto commit (default = 10s)"},
    {"icmt", 0, "sec", OPTION_ALIAS, "Hello"},
    {"push-interval", 'p', "seconds", 0,
     "Interval for remote push. If not passed remote push will be disabled"},
    {"max-commit", 'm', "number", 0,
     "Maximum number of commits autogit will perform."},
    {}

};

struct argp argp = {options, parse_args};

void init_parser(int argc, char **argv) {
  argp_parse(&argp, argc, argv, 0, 0, 0);
  init_autogit(&autogit_props);
}

#endif