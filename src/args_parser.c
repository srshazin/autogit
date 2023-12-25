#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#define MAX_ARG_S 10
#define TRUE 1
#define FALSE 0

static Arg args[MAX_ARG_S];
static unsigned int last_entry_index = 0;

/**
 * __register_arg_entry() returns Arg array
 */

static void __register_arg_entry(const char *args_primary, const char *arg_shorthand, const char *help_desc, int requireValue, int isFlag);
Arg **get_registered_args()
{
    return args;
}
/*
 * The init function  loads the argument values to the parser during runtime.
 * The orders of callng __register_arg_entry() function will matter during the application running time
 */
void init_arg_parser()
{
    __register_arg_entry("--help", "-h", "Display this help message", 0, 0);
    __register_arg_entry("--version", "-V", "Display version information", 0, 0);
    __register_arg_entry("--interval", "-i", "<seconds> Specify after how much time it should auto commit", 1, 0);
    __register_arg_entry("--max-commit", "-m", "Specify a boundary value for maximum amount of commit(default=infinity)", 1, 0);
    __register_arg_entry("branch", "-b", "<branch_name> Specify any different branch that current one", 1, 0);
    __register_arg_entry("-verbose", "--v", "verbosely log everything", 0, 1);
}

/**
 * Function that returns the count of registered arguments
 */

int get_registered_args_nums()
{
    return last_entry_index;
}

/**
 * parse_args() this function parse the arguments and checks for matches with the registers
 */
void parse_args(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 0; i < argc; i++)
        {
            printf("%s\n", argv[i]);
            if (is_arg_in_register(argv[i]) == 0)
            {
                printf("Unknown argument\nPlease use --help[-h] for listing all available arguments.\n", argv[i]);
            }
        }
    }
    else
    {
        printf("Not enought argument provided\n");
    }
}

static void __register_arg_entry(const char *args_primary, const char *arg_shorthand, const char *help_desc, int requireValue, int isFlag)
{
    Arg __arg;
    __arg.arg_primary = args_primary;
    __arg.arg_shorthand = arg_shorthand;
    __arg.help_desc = help_desc;
    __arg.requireValue = requireValue;
    __arg.isFlag = isFlag;
    args[last_entry_index] = __arg;
    last_entry_index++;
}
