#ifndef SHELL_H
#define SHELL_H

typedef struct {
    int code;
    char *output;
    char *error;
    char *pwd;
} output_struct;

extern output_struct* output_p;
void err_f(char*);
void out_f(char*);
void get_cwd();
int run_c(char*);

#endif
