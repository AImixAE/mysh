#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin.h"
#include "color.h"

#define MYSH_TOK_DELIM " \t\r\n"
#define MYSH_TOK_BUFFER_SIZE 64

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

int mysh_launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int mysh_execute(char **args) {
    if (args[0] == NULL) return 1;

    for (int i = 0; i < mysh_builtin_nums(); i++)
        if (strcmp(args[0], builtin_cmd[i]) == 0)
            return (builtin_func[i])(args);

    return mysh_launch(args);
}

char *mysh_read_line() {
    char *line = NULL;
    size_t bufsize;
    getline(&line, &bufsize, stdin);
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
    char *line;   // 输入命令
    char **args;  // 存储参数
    int status;   // 命令状态

    do {
        // 获取当前位置
        char path[100];
        getcwd(path, 100);

        // shell前缀
        printf(GREEN "[ " YELLOW "mysh " MAGENTA "( %s )" RESET GREEN "]\n",
               path);
        printf("==> " RESET);

        line = mysh_read_line();       // 读取命令
        args = mysh_split_line(line);  // 分词
        status = mysh_execute(args);   // 执行命令 获取返回值

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char *argv[]) {
    mysh_loop();

    return 0;
}