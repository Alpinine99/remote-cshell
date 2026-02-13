#ifndef FORMATTER_H
#define FORMATTER_H

typedef struct {
    char* prompt;
    char* prompt_color;
    char* output_color;
} config;

int print_f(char*, config);
int print_n(char*);

#endif
