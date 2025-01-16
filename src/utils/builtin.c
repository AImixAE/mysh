#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// readline
#include <readline/history.h>

#include "builtin.h"
#include "color.h"

char *builtin_cmd[] = {"cd", "help", "exit", "history", "set", "get"};

int (*builtin_func[])(char **) = {&mysh_cd,      &mysh_help, &mysh_exit,
                                  &mysh_history, &mysh_set,  &mysh_get};

int mysh_builtin_nums() { return sizeof(builtin_cmd) / sizeof(builtin_cmd[0]); }

int mysh_cd(char **args) {
    if (args[1] == NULL) {
        puts("cd: lack of args");
        return 1;
    }

    if (chdir(args[1]) != 0) perror("chdir");

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

int mysh_history(char **args) {
    // 输出历史
    int len = history_length;

    for (int i = 0; i < len; i++) {
        HIST_ENTRY *entry = history_get(i);
        if (entry != NULL) {
            printf(BLUE "%d| " RESET "%s\n", i, entry->line);
        }
    }

    return 1;
}

int mysh_set(char **args) {
    if (args[2] == NULL) {
        puts("set: need 2 args");
        return 1;
    }

    // 还无法运行
    // 有空再修吧
    setenv(args[1], args[2], 1);

    return 1;
}

int mysh_get(char **args) {
    if (args[1] == NULL) {
        puts("get: need an arg");
        return 1;
    }

    printf("%s = %s\n", args[1], getenv(args[0]));

    return 1;
}
