#include "utils.h"
#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

// function to register the arguments
void init_arg_parser();
void parse_args(int argc, char ** argv);
Arg ** get_registered_args();
int get_registered_args_nums();

#endif