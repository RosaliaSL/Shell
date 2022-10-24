#include <unistd.h>
#include <stdio.h>
#include <string.h>

void pwd() {
    char presentWorkingDirectory[1000];
    printf("Current Working Directory: %s \n", getcwd(presentWorkingDirectory, sizeof(presentWorkingDirectory)));
}

// int main(int argc, char* argv[]) {
//     if (argc == 2 && strcmp( argv[1], "pwd") == 0) {
//         pwd();
//     } else {
//         printf("Incorrect Parameters\n");
//     }
// }

/*
void main(int argc) {
    if (argc == 1) {

    }
}
*/