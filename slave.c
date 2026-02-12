#include "common.h"
#include "shell.h"
#include <stdio.h>


int main() {
    char *cmd = "ls";
    
    if (run_c(cmd) == 0) {
	printf("out - %s\n\n", output_p -> output);
	printf("pwd - %s\n\n", output_p -> pwd);
	printf("code - %d\n", output_p -> code);
    }

    return 0;
}


