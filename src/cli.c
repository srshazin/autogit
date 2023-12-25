#include <stdio.h>
#include <stdlib.h>

void get_git_status()
{
    char *cmd = "git status | tail -n +6";
    char buffer[4048];
    // Open a pipe to the command
    FILE *pipe = popen(cmd, "r");

    if (pipe == NULL)
    {
        perror("Error opening pipe");
        return 1;
    }

    // Read the output of the command
    int total_buffer_line = 0;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        printf("%s", buffer);
        total_buffer_line++;
    }
    printf("\nTotal changes: %i \n", total_buffer_line);

    // Close the pipe
    int status = pclose(pipe);

    // Check the exit status
    if (status == -1)
    {
        perror("Error closing pipe");
        return 1;
    }

    printf("Command exited with status %d\n", status);
}