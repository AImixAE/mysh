#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"

char *builtin_cmd[] = {"cd", "help", "exit"};

int (*builtin_func[])(char **) = {&mysh_cd, &mysh_help, &mysh_exit};

int mysh_builtin_nums() { return sizeof(builtin_cmd) / sizeof(builtin_cmd[0]); }

int mysh_cd(char **args) {
    if (args[1] == NULL) {
        puts("cd: lack of args");
    } else {
        if (chdir(args[1]) != 0) perror("chdir");
    }

    return 1;
}

int mysh_help(char **args) {
    puts("My Shell");
    puts("Version: 1.0\n");

    puts("Builtin commands:");
    for (int i = 0; i < mysh_builtin_nums(); i++)
        printf("  %s\n", builtin_cmd[i]);

    return 1;
}

int mysh_exit(char **args) { return 0; }