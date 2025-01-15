#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            printf("%s", argv[i]);
            if (i < argc - 1) {
                printf(" ");
            }
        }
        printf("\n");
    } else {
        // 查看环境变量
        char *var = getenv("PATH");
        if (var != NULL) {
            printf("PATH: %s\n", var);
        } else {
            printf("PATH environment variable not found.\n");
        }
    }
    return 0;
}