#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "cli.h"
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
    unsigned int pos = 1;
    if (argc > 1)
    {
        // for (int i = 1; i < argc; i++)
        // {
        //     printf("%s\n", argv[i]);
        //     if (is_arg_in_register(argv[i]) == 0)
        //     {
        //         printf("Unknown argument{%s}\nPlease use --help[-h] for listing all available arguments.\n", argv[i]);
        //     }
        //     else
        //     {
        //         // Check for valued arg or not
        //         Arg arg__ = find_arg_in_register(argv[i]);
        //         if (arg__.arg_primary != NULL)
        //         {
        //             if (arg__.requireValue == 1)
        //             {
        //                 if (
        //                     strcmp(arg__.arg_primary, "--interval") ||
        //                     strcmp(arg__.arg_shorthand, "-i"))
        //                 {
        //                     // TODO: handle interval
        //                     printf("Interval is set to %s\n", argv[i + 1]);
        //                 }
        //             }
        //         }
        //     }
        // }
        if (is_arg_match_target(argv[pos], "-interval", "-i"))
        {
            if (argc > 2)
            {
                // check if 0 for infinity

                unsigned int interval = atoi(argv[pos + 1]);
                if (interval != 0)
                {
                    if (interval >= 5)
                    {
                        printf("Manual checkup interval set to %is\n", interval);
                        printf("Running immediate call...\n");
                        get_git_status();
                    }
                    else
                    {
                        printf("Couldn't set %is as interval, minimum interval period is 5 seconds.\n", interval);
                    }
                }
                else
                {
                    printf("Invalid interval period(exit)\n");
                }
            }
        }
    }
    else
    {
        printf("Not enough argument provided\n");
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
