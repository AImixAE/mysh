#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin.h"
#include "exec.h"

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