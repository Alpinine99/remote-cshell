#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"
#include "common.h"

int print_f(char *text, config _config)
{
    char prompt[256];
    char output[strlen(text) + 1];

    // Find the last occurrence of '\n'
    char *last_newline = strrchr(text, '\n');

    if (last_newline != NULL)
    {
        // Copy the last line (after the last \n)
        strcpy(prompt, last_newline + 1);

        // Calculate the length of the part before last \n
        size_t len = last_newline - text;

        // Copy the output of the string
        strncpy(output, text, len);
        output[len] = '\0'; // null terminate
    }
    else
    {
        // No newline found, entire string is one line
        strcpy(prompt, text);
        output[0] = '\0';
    }

    printf("%s%s\n" RESET, _config.output_color, output);
    printf("%s╭─[%s]\n╰─$ " RESET, _config.prompt_color, prompt);
    fflush(stdout);
    return 0;
}
