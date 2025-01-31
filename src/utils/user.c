#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "color.h"
#include "exec.h"
#include "token.h"
#include "user.h"

char *mysh_read_line() {
    char *line = readline(GREEN "==> " RESET);
    if (line && *line) {
        add_history(line);
    }
    return line;
}

char **mysh_split_line(char *line) {
    int buffer_size = MYSH_TOK_BUFFER_SIZE, position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    token = strtok(line, MYSH_TOK_DELIM);

    while (token != NULL) {
        tokens[position++] = token;
        token = strtok(NULL, MYSH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

void mysh_loop() {
    char *line;
    char **args;
    int status;

    do {
        char path[100];
        getcwd(path, 100);

        printf(GREEN "[ " YELLOW "mysh " MAGENTA "( %s )" RESET GREEN
                     "]\n" RESET,
               path);

        line = mysh_read_line();
        args = mysh_split_line(line);
        status = mysh_execute(args);

        free(line);
        free(args);
    } while (status);
}
