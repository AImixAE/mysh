int mysh_cd(char **args);
int mysh_help(char **args);
int mysh_exit(char **args);

int mysh_builtin_nums();

extern int (*builtin_func[])(char **);
extern char *builtin_cmd[];
