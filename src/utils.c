#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "args_parser.h"
#include <math.h>

void printHelp()
{
    Arg *__args = get_registered_args();
    printf("Usage:\n");
    printf("\tautogit [options]\n\n");
    printf("Options:\n");
    for (int i = 0; i < get_registered_args_nums(); i++)
    {
        Arg __arg = __args[i];
        printf("\t%-3s%-25s%s\n", __arg.arg_shorthand, __arg.arg_primary, __arg.help_desc);
    }
}

/**
 * is_arg_in_register() checks if a passed argument is present in the registered argument list
 */

int is_arg_in_register(const char *argument)
{
    Arg *registered_args = get_registered_args();
    // A simple linear search
    for (int i = 0; i < get_registered_args_nums(); i++)
    {
        if (strcmp(argument, registered_args[i].arg_primary) == 0 || strcmp(argument, registered_args[i].arg_shorthand) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * log_error(char * error) A simple utility function to print an error message
 */

void log_error(char *error_msg)
{
    printf("%d\n", error_msg);
}
