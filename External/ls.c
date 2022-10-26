#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void ls(const char* dirname, int flag_a, int flag_R) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        if (errno == ENOENT) {
            perror("Directory does not exist");
        } else {
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }

    printf("Reading files in: %s\n", dirname);

    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL) {
        if (!flag_a && entity->d_name[0] == '.') {
            entity = readdir(dir);
            continue;
        }
        printf("%s/%s\n", dirname, entity->d_name);
        if (flag_R && entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            printf("\n");
            char path[100] = {};
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            ls(path, flag_a, flag_R);
            printf("\n");
        }
        entity = readdir(dir);
    }

    closedir(dir);
}

int main(int argc, const char *argv[]) {
    // printf("Executing ls\n");
    // printf("%d\n", argc);

    if (argc == 1) {
        printf("Hello\n");
        ls(".", 0, 0);
    } else if (argc == 2) {
        if (argv[1][0] == '-') { // checking if option is passed
            // options supporting: a, R
            int flag_a = 0, flag_R = 0;
            char *p = (char *)(argv[1] + 1);
            while (*p) {
                if (*p == 'a') flag_a = 1;
                else if (*p == 'R') flag_R = 1;
                else {
                    perror("Unknown option error");
                    exit(EXIT_FAILURE);
                }
                p++;
            }
            ls(".", flag_a, flag_R);
        } else {
            ls(argv[1], 0, 0);
        }
    } else if (argc == 3) {
        if (argv[1][0] != '-') {
            perror("Incorrect Usage Error");
            exit(EXIT_FAILURE);
        }
        int flag_a = 0, flag_R = 0;
        char *p = (char *)(argv[1] + 1);
        while (*p) {
            if (*p == 'a') flag_a = 1;
                else if (*p == 'R') flag_R = 1;
                else {
                    perror("Unknown option error");
                    exit(EXIT_FAILURE);
                }
                p++;
        }
        ls(argv[2], flag_a, flag_R);
    }
    return 0;
}