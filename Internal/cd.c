#include <stdio.h>
#include <stdlib.h> // getenv() function requires this import
#include <string.h>
#include <unistd.h> // chdir() declared in unistd
#include "pwd.c"

int cd(char* arg){
	// If we write no path (only 'cd'), then go to the home directory
	if (arg == NULL) {
		chdir(getenv("HOME")); 
        pwd();
		return 1;
	}
	/*
    Else we change the directory to the one specified by the argument
    This case will handle two cases:
    - cd .. (Go to the directory above the current directory in the tree)
    - cd ~ (Go to root)
    - cd specified-directory (Goes to the specified directory)
    */ 
    else if (chdir(arg) == 0) {
        printf("Directory Changed.\n");
        pwd();
    // Specified directory not found
    } else if (chdir(arg) == -1) {
		printf(" %s: no such directory\n", arg);
        return -1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
    if (argc <= 1 || argc > 3) {
        printf("Incorrect number of parameters\n");
    }
    else if (argc >= 2 && strcmp( argv[1], "cd") == 0) {
        cd(argv[2]);
    } 
}