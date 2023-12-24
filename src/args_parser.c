#include <stdlib.h>
#include <stdio.h>
#define MAX_ARG_ 10

void parse_args(int argc, char ** argv){
    for (int i = 0 ; i < argc; i++){
        printf("%s\n", argv[i]);
    }
}