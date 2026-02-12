#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "shell.h"

output_struct *output_p;
output_struct output;

void err_f(char* error_m) {
    output.error = malloc(strlen(error_m) + 10);
    sprintf(output.error, "error - %s", error_m);
    output.code = 1;
}

void out_f(char* results) {
    output.output = malloc(strlen(results) + 1);
    sprintf(output.output, results);
    output.code = 0;
}

void get_cwd() {
    long size = pathconf(".", _PC_PATH_MAX);
    if (size == -1) size = 1024; // fallback
    char *cwd = malloc(size);
    if (cwd == NULL) {
        err_f("malloc failed!");
        return;
    }
    if (getcwd(cwd, size) != NULL) {
	output.pwd = malloc(strlen(cwd) + 1);
        sprintf(output.pwd, cwd);
    } else {
        err_f("getcwd() failed!");
    }
    free(cwd);
}

int run_c(char *cmd) {
    FILE *fp = popen(cmd, "r");
    size_t buffer_size = 1024;
    char buffer[buffer_size];
    char* results = malloc(buffer_size);

    if (fp == NULL)
        err_f("popen failed");
    else if (results == NULL)
        err_f("malloc failed!");
    else {
	results[0] = '\0';
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
	    size_t len = strlen(results);
            size_t chuck_len = strlen(buffer);
	    
	    if (len + chuck_len + 1 > buffer_size) {
	        buffer_size *= 2;
		results = realloc(results, buffer_size);
		if (results == NULL) {
	            err_f("realloc failed!");
		    break;
		}
	    }
	    strcat(results, buffer);
	}
	out_f(results);
    }

    get_cwd();
    output_p = &output;
    free(results);
    pclose(fp);
    return output.code;
}

