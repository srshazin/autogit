#include <stdio.h>
#include "utils.h"
#include "args_parser.h"
#include <argp.h>
int main(int argc, char **argv)
{
    // printHelp();
    init_arg_parser();
    printf("Total args: %i; first arg at pos 0: %s\n\n", argc, argv[0]);
    // printf("Hello world \n");
    parse_args(argc, argv);
    return 0;
}