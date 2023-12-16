#include <stdio.h>
#include "utils.h"
#include <math.h>
static void add_help_entry(char * opt, char * description){
    printf("\t%s\t\t%s\n", opt, description);
}

void printHelp(){
    printf("Usage:\n");
    printf("\tautogit [options]\n\n");

    printf("Options:\n");
    printf("\t-h, --help\t\tDisplay this help message\n");
    printf("\t-v, --version\t\tDisplay version information\n");
    printf("\t-i, --interval\t\t<seconds> Specify how after how much time it should auto commit\n");
    add_help_entry("-n, --commit", "Specify a boundary value for maximum amount of commit(default=infinity)");
    add_help_entry("-b , branch", "[branch_name] Specify any branch (default: active branch during calling autogit)");
    add_help_entry("-V, --verbose", "verbosely log everything");
    
}