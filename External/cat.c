#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat_stdin() {
    int bufferSize = 4096;
    char buffer[bufferSize];

    while (fgets(buffer, bufferSize, stdin)) {
        int len = strlen(buffer);
        buffer[len - 1] = '\0';
        fprintf(stdout, "%s\n", buffer);
    }
}

void cat_singleFile(int argc, char *argv[], int currentFileIdx, int flag_s, int flag_b) {
    int bufferSize = 4096;
    char buffer[bufferSize];

    FILE *fptr = fopen(argv[currentFileIdx], "rb");
    if (fptr == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory", argv[currentFileIdx]);
        exit(1);
    }
    
    int lastLineBlank = 0;
    int lineNumber = 1;

    while (fgets(buffer, bufferSize, fptr)) {
        int length = strlen(buffer);
        if (flag_s) {
            length = strlen(buffer);
            int currentLineBlank = (length <= 1) ? 1 : 0;
            if (lastLineBlank && currentLineBlank) {
                continue;
            }
            lastLineBlank = currentLineBlank;
        }

        if (flag_b) {
                length = strlen(buffer);
                if (length >= 1) {
                    char *tmp = strdup(buffer);
                    buffer[0] = '\0';
                    sprintf(buffer, "%*d\t", 6,  lineNumber++);
                    strcat(buffer, tmp);
                }
        }
        fprintf(stdout, "%s", buffer);
    }
    fclose(fptr);
}

int main(int argc, char *argv[]) {
    int flag_s = 0, flag_b = 0;
    if (argc < 1) {
        perror("Unknown option error");
        exit(EXIT_FAILURE);
    } else if (argc > 1) {
        if (argv[1][0] != '-') {
            int currentFileIdx = 1;
            while (currentFileIdx < argc) {
                cat_singleFile(argc, argv, currentFileIdx, 0, 0);
                currentFileIdx++;
            }
        } else if (argv[1][0] == '-' && argv[1][1] == 's') {
            flag_s = 1;
            cat_singleFile(argc, argv, argc - 1, 1, 0);
        } else if (argv[1][0] == '-' && argv[1][1] == 'b') {
            flag_b = 1;
            cat_singleFile(argc, argv, argc - 1, 0, 1);
        } else {
            perror("Unknown option error");
            exit(EXIT_FAILURE);
        }
    } else {
        cat_stdin();
    }
    return 0;
}