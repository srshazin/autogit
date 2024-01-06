#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * log_error(char * error) A simple utility function to print an error message
 */

void log_error(char *error_msg) { printf("%s\n", error_msg); }

/**
 * char *read_pipe(const char *cmd); to execute command and get their respose in
 * return as a string buffer\
 */

char *read_pipe(const char *cmd) {
  char *buffer = NULL;
  size_t buffer_size = 0;
  ssize_t read_bytes;
  size_t total_return_buffer_size = 0;
  // Open a pipe to the command
  FILE *pipe = popen(cmd, "r");

  if (pipe == NULL) {
    perror("Error opening pipe");
    return NULL;
  }

  while ((read_bytes = getline(&buffer, &buffer_size, pipe)) != -1) {
    total_return_buffer_size += read_bytes;
  }

  // Close the pipe
  int status = pclose(pipe);

  // Check the exit status
  if (status == -1) {
    perror("Error closing pipe");
    return NULL;
  }

  // Allocate memory for output string
  char *output = (char *)malloc(total_return_buffer_size + 1);
  if (output == NULL) {

    perror("Memory allocation failed!");
    free(buffer);
    return NULL;
  }
  strcpy(output, buffer);
  free(buffer);
  return output;
}
