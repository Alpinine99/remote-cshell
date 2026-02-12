#ifndef FORMATTER_H
#define FORMATTER_H

typedef struct {
    string prompt;
    char prompt_color[10];
    char output_color[10];
} config;

int print_f(string, config);
int print_n(string);

#endif
