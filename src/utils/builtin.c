#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/history.h>

#include "builtin.h"
#include "color.h"
#include "vars.h"

char *builtin_cmd[] = {"cd", "help", "exit", "history", "ver", "set", "get"};

int (*builtin_func[])(char **) = {&mysh_cd,      &mysh_help, &mysh_exit,
                                  &mysh_history, &mysh_ver,  &mysh_set,
                                  &mysh_get};

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

int mysh_ver(char **args) {
    printf(GREEN "My Shell " BLUE "Version " CYAN "%s" RESET "\n", MYSH_VER);

    return 1;
}

int mysh_set(char **args) {
    // 检查 args 数组的有效性
    if (args[1] == NULL || args[2] == NULL) {
        puts("set: need 2 valid arguments");
        return 1;
    }

    // 检查环境变量名是否合法
    char *var_name = args[1];
    if (*var_name == '\0' || *var_name >= '0' && *var_name <= '9') {
        puts("set: invalid environment variable name");
        return 1;
    }
    for (char *p = var_name; *p != '\0'; p++) {
        if (*p == '=') {
            puts("set: environment variable name cannot contain '='");
            return 1;
        }
    }

    // 调用 setenv 并检查返回值
    if (setenv(args[1], args[2], 1) != 0) {
        perror("set");
    }

    return 1;
}

int mysh_get(char **args) {
    if (args[1] == NULL) {
        puts("get: need an arg");
        return 1;
    }

    printf("%s = %s\n", args[1], getenv(args[1]));

    return 1;
}
