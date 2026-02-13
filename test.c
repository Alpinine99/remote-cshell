#include "formatter.h"
#include "common.h"

int main() {

    config my_config = {.prompt_color = YELLOW, .output_color = CYAN};
    char *message = "Hello\ndaddy\nhow are\nyou\n/home/coderdree/Desktop";
    
    print_f(message, my_config);

    return 0;
}
