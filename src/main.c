#include <stdio.h>

#include "builtin.h"
#include "version.h"
#include "exec.h"
#include "user.h"
#include "color.h"

int main(int argc, char *argv[]) {
    printf(GREEN "My Shell " BLUE "Version " CYAN "%s" RESET "\n",
           mysh_get_version());

    mysh_loop();

    return 0;
}
