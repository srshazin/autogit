#ifndef UTILS_H
#define UTILS_H
#define NEARG "Not enough argument please type --help[-h] for help"
typedef struct
{
    char *arg_primary;
    char *arg_shorthand;
    char *help_desc;
    int requireValue;
    int isFlag;
} Arg;

void printHelp();
int is_arg_in_register(const char *argument);
void log_error(char *error_msg);
Arg find_arg_in_register(char *key);
int is_arg_match_target(
    const char *provided_arg,
    const char *match_with,
    char *alias);

char *exec_cmd(const char *cmd);
#endif