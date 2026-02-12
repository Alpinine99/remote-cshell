#include "common.h"
#include "shell.h"
#include <stdio.h>


int main() {
    char *cmd = "ls";
    
    if (run_c(cmd) == 0) {
	printf("%s\n", output_p -> output);
    }

    return 0;
}


