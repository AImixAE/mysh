#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir;
    struct dirent *ent;

    dir = opendir(".");
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir");
        return 1;
    }
    return 0;
}
