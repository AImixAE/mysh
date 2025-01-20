#include <stdio.h>

#include "builtin.h"
#include "vars.h"
#include "exec.h"
#include "user.h"
#include "color.h"

int main(int argc, char *argv[]) {
    printf(GREEN "My Shell " BLUE "Version " CYAN "%s" RESET "\n", MYSH_VER);

    mysh_loop();

    return 0;
}
