#include <stdio.h>
#include "utils.h"
#include "args_parser.h"
#include <argp.h>
int main(int argc, char ** argv) {
    // printHelp();
    printf("Hello world \n");
    parse_args(argc, argv);
    return 0;
}