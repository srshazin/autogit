#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <argp.h>
#include "utils.h"
#include "text_parser.h"
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
// void init_arg_parser()
// {
//     __register_arg_entry("--help", "-h", "Display this help message", 0, 0);
//     __register_arg_entry("--version", "-V", "Display version information", 0, 0);
//     __register_arg_entry("--interval", "-i", "<seconds> Specify after how much time it should auto commit", 1, 0);
//     __register_arg_entry("--max-commit", "-m", "Specify a boundary value for maximum amount of commit(default=infinity)", 1, 0);
//     __register_arg_entry("branch", "-b", "<branch_name> Specify any different branch that current one", 1, 0);
//     __register_arg_entry("-verbose", "--v", "verbosely log everything", 0, 1);
// }

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
// void parse_args(int argc, char **argv)
// {
//     unsigned int pos = 1;
//     if (argc > 1)
//     {
//         // for (int i = 1; i < argc; i++)
//         // {
//         //     printf("%s\n", argv[i]);
//         //     if (is_arg_in_register(argv[i]) == 0)
//         //     {
//         //         printf("Unknown argument{%s}\nPlease use --help[-h] for listing all available arguments.\n", argv[i]);
//         //     }
//         //     else
//         //     {
//         //         // Check for valued arg or not
//         //         Arg arg__ = find_arg_in_register(argv[i]);
//         //         if (arg__.arg_primary != NULL)
//         //         {
//         //             if (arg__.requireValue == 1)
//         //             {
//         //                 if (
//         //                     strcmp(arg__.arg_primary, "--interval") ||
//         //                     strcmp(arg__.arg_shorthand, "-i"))
//         //                 {
//         //                     // TODO: handle interval
//         //                     printf("Interval is set to %s\n", argv[i + 1]);
//         //                 }
//         //             }
//         //         }
//         //     }
//         // }
//         if (is_arg_match_target(argv[pos], "-interval", "-i"))
//         {
//             if (argc > 2)
//             {
//                 // check if 0 for infinity
//                 unsigned int interval = atoi(argv[pos + 1]);
//                 if (interval != 0)
//                 {
//                     if (interval >= 5)
//                     {
//                         printf("Manual checkup interval set to %is\n", interval);
//                         printf("Running immediate call...\n");
//                         parse_git_status();
//                     }
//                     else
//                     {
//                         printf("Couldn't set %is as interval, minimum interval period is 5 seconds.\n", interval);
//                     }
//                 }
//                 else
//                 {
//                     printf("Invalid interval period(exit)\n");
//                 }
//             }
//         }
//         if (is_arg_match_target(argv[pos], "--help", "-h"))
//         {
//             if (argv[pos + 1] == NULL)
//             {
//                 printHelp();
//             }
//             else
//             {
//                 printf("Invalid argument %s %s", argv[pos], argv[pos + 1]);
//             }
//         }
//         if (
//             is_arg_match_target(argv[pos], "--push-interval", "-p") ||
//             is_arg_match_target(argv[pos + 2], "--push-interval", "-p") ||
//             is_arg_match_target(argv[pos + 4], "--push-interval", "-p"))
//         {
//             printf("Setting up push interval \n");
//         }
//     }
//     else
//     {
//         printf("Not enough argument provided\n");
//     }
// }

// Define a structure to hold command-line arguments
struct arguments
{
    char *input_file;
    int verbose;
};

// Define a parser function for argp
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch (key)
    {
    case 'i':
        arguments->input_file = arg;
        break;
    case 'v':
        arguments->verbose = 1;
        break;
    case ARGP_KEY_END:
        if (arguments->input_file == NULL)
        {
            argp_error(state, "Input file is required.");
        }
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// Define the argp structure
static struct argp argp = {
    .options = {
        {"input", 'i', "FILE", 0, "Input file", 0},
        {"verbose", 'v', 0, 0, "Enable verbose output", 0},
        {0}},
    .parser = parse_opt,
    .args_doc = "FILE",
    .doc = "A simple program to demonstrate argp",
};

void parse_args(int argc, char *argv[])
{
    struct arguments arguments;

    // Set default values
    arguments.input_file = NULL;
    arguments.verbose = 0;

    // Parse command-line arguments
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // Display parsed values
    printf("Input file: %s\n", arguments.input_file);
    printf("Verbose: %d\n", arguments.verbose);
}
