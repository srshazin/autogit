#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "utils.h"
#include "args_parser.h"

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
 * find_arg_in_register(): finds a specific argument in the register and returns an Arg struct corresponding that
 * if something wrong happens a null struct is returned
 */

Arg find_arg_in_register(char *argument)
{
    Arg *registered_args = get_registered_args();
    // A simple linear search
    for (int i = 0; i < get_registered_args_nums(); i++)
    {
        if (strcmp(argument, registered_args[i].arg_primary) == 0 || strcmp(argument, registered_args[i].arg_shorthand) == 0)
        {
            return registered_args[i];
        }
    }
    // If the loop doesn't break and ends we send a null Arg
    Arg __arg = {NULL, NULL, NULL, NULL, NULL};
    return __arg;
}

/**
 * is_arg_match_target(): basically tells if a passed argument is this or that
 * returns true of false
 */

int is_arg_match_target(
    const char *provided_arg,
    const char *match_with,
    char *alias)
{
    if (strcmp(provided_arg, match_with) == 0 || strcmp(provided_arg, alias) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * log_error(char * error) A simple utility function to print an error message
 */

void log_error(char *error_msg)
{
    printf("%d\n", error_msg);
}

/**
 * char *exec_cmd(const char *cmd); to execute command and get their respose in return as a string buffer\
 */

char *exec_cmd(const char *cmd)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_bytes;
    size_t total_return_buffer_size = 0;
    // Open a pipe to the command
    FILE *pipe = popen(cmd, "r");

    if (pipe == NULL)
    {
        perror("Error opening pipe");
        return 1;
    }

    while ((read_bytes = getline(&buffer, &buffer_size, pipe)) != -1)
    {
        total_return_buffer_size += read_bytes;
    }

    // Close the pipe
    int status = pclose(pipe);

    // Check the exit status
    if (status == -1)
    {
        perror("Error closing pipe");
        return 1;
    }

    // Allocate memory for output string
    char *output = (char *)malloc(total_return_buffer_size + 1);
    if (output == NULL)
    {

        perror("Memory allocation failed!");
        free(buffer);
        return NULL;
    }
    strcpy(output, buffer);
    free(buffer);
    return output;
}
