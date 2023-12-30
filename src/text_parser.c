#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
/**
 * int parse_git_status() parses the git status output and make  a file out of it called .autogit
 */
int parse_git_status()
{
    char *git_status = exec_cmd("git status");
    if (git_status == NULL)
    {
        perror("Couldn't allocate needed memory.");
        return 0;
    }
    printf("%zu\n", strlen(git_status));
    printf("%s", git_status);

    // Free the allocated memory
    free(git_status);
    return 1;
}