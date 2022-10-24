#include <stdio.h>
#include<string.h>

void echo(int argc, char* argv[]) {
    int i;
    if (argc == 2) {
        printf("\n");
    } else {
        for (i = 2; i < argc; i++) {
            printf("%s ", argv[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc >= 2 && strcmp( argv[1], "echo") == 0) {
        echo(argc, argv);
    } else {
        printf("Incorrect Parameters\n");
    }
}
