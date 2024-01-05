#ifndef UTILS_H
#define UTILS_H

void printHelp();

void log_error(char *error_msg);

char *read_pipe(const char *cmd);
#endif