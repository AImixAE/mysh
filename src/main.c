#include <stdio.h>

#include "builtin.h"
#include "defines.h"
#include "exec.h"
#include "user.h"
#include "color.h"

int main(int argc, char *argv[]) {
    printf(GREEN "My Shell " BLUE "Version " CYAN mysh_ver RESET "\n");

    mysh_loop();

    return 0;
}
