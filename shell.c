#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void initializeShell() {
    printf("\n\t################################################\n");
    printf("\t          Shell by Rosalia Steffi Longjam \n");
    printf("\t################################################\n\n");
}

void printCurrentDirectory() {
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s$ ", cwd);
}

char* readinput() {
    char* input;
    size_t size = 100;
    size_t curr_line;
    input = (char*)malloc(size*sizeof(char));
    curr_line = getline(&input, &size, stdin);

    if(curr_line == -1){
        printf("Error: Couldn't allocate memory to input\n");
        exit(1);
    }
    return input;
}

char **parse(char* input){
	int pos = 0;
	char **tokens = calloc(1024, (sizeof(char*) + 1));
	char *token;
	token = strtok(input, " \n");
	while(token != NULL){
		tokens[pos] = token;
		pos++;
		token = strtok(NULL, " \n");
	}
    tokens[pos] = "\0";
	return tokens;
}

int echo(int argc, char* argv[]) {
    int i;
    if (argc == 1) {
        printf("\n");
    } else {
        for (i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    return 1;
}

int pwd(int argc, char* argv[]) {
    char presentWorkingDirectory[1000];
    printf("Current Working Directory: %s \n", getcwd(presentWorkingDirectory, sizeof(presentWorkingDirectory)));
    return 1;
}

int cd(int argc, char** command) {
    if (argc > 2) {
        printf("Incorrect number of parameters\n");
        return 1;
    } if (argc == 1) {
        chdir(getenv("HOME")); 
    } else if (strcmp(command[1], "~") == 0) {
        chdir(getenv("HOME")); 
    } else if (chdir(command[1]) == 0) {
        // printf("Directory Changed.\n");
    } else if (chdir(command[1]) == -1) {
		printf("%s: no such directory\n", command[1]);
	}
    return 1;
}

int checkAndExecuteInternal(int argc, char** command) {
    if (strcmp(command[0], "cd") == 0) {
        return cd(argc, command);
	}
	if (strcmp(command[0], "pwd") == 0) {
	    return pwd(argc, command);
	}
	if (strcmp(command[0], "echo") == 0) {
	    return echo(argc, command);
	}
    if (strcmp(command[0], "exit") == 0) {
	    exit(0);
	}
    return 0;
}

int main() {
    initializeShell();
    int shouldExit = 0;
    int isInternalCommand = 0, isExternalCommand = 0;

    while (!shouldExit) {
        printCurrentDirectory();

        char *inputString;
        inputString = readinput();
        
        if (strcmp(inputString, "\n") == 0) {
            continue;
        } else {
            char** command = parse(inputString);
            
            int argc = 0;
            while(strcmp(command[argc], "\0") != 0){
                // printf("%s\n", parsed[i]);
                argc++;
            }
            // printf("%d\n", argc);
            isInternalCommand = checkAndExecuteInternal(argc, command);
        }
    }

    return 0;
}