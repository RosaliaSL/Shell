#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char origin[1024];

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
        if(strcmp(argv[1], "-n") == 0){ //option to print the given statement without any \n for the next terminal prompt
            for(i = 2; i < argc-1; i++){
                printf("%s ", argv[i]);
            }
            printf("%s", argv[i]);
        }
        else if(strcmp(argv[1], "--help") == 0){ //displays the help page
            char cwd[1024];
	        getcwd(cwd, sizeof(cwd));
            chdir("/");
            chdir(origin);
            chdir("Descriptions");
            FILE *fp;
            fp = fopen("echo.txt", "r");
            char *fline = NULL;
            size_t flen = 0;
            while(getline(&fline, &flen, fp) != -1){
                printf("%s", fline);
            }
            printf("\n");
            fclose(fp);
            chdir("/");
            chdir(cwd);
        }
        else{
            for(i = 1; i < argc; i++){ //no option implemented, it will print wrong/invalid options as well (error case handled)
                printf("%s ", argv[i]);
            }
            printf("\n");
        }
    }
    return 1;
}

int pwd(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Current Working Directory: %s \n", getenv("PWD"));
    }
    else if(argc == 2) {
        if (strcmp(argv[1], "-L") == 0) {
            printf("Current Working Directory: %s \n", getenv("PWD"));
        }
        else if(strcmp(argv[1], "-P") == 0){
            char presentWorkingDirectory[1000];
            printf("Current Working Directory: %s \n", getcwd(presentWorkingDirectory, sizeof(presentWorkingDirectory)));
        }
        else{
            printf("Invalid option\n");
        }
    }
    else{
        printf("Invalid option");
    }
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

void checkAndExecuteExternal(int argc, char** command) {
    if (strcmp(command[0], "cat") == 0) {

	} else if (strcmp(command[0], "date") == 0) {

	} else if (strcmp(command[0], "ls") == 0) {

	} else if (strcmp(command[0], "mkdir") == 0) {

	} else if (strcmp(command[0], "rm") == 0) {

	} else {
        printf("command not found: %s\n", command[0]);
    }
    return;
}

int main() {
    initializeShell();
    int shouldExit = 0;
    int isInternalCommand = 0;
    getcwd(origin, sizeof(origin));

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
            if (!isInternalCommand) {
                pid_t pid = fork();
                if (pid < 0) {
				    printf("Error in creating child process.\n");
                } else if (pid == 0) {
                    printf("Created child process.\n");
                    // printf("%s\n", command[0]);
                    checkAndExecuteExternal(argc, command);
                } else if (pid > 0) {
                    pid_t p_temp = waitpid(pid, NULL, WUNTRACED);
				    if(p_temp < 0) {
					    printf("Error no %d\n", errno);
					    perror("waitpid");
				    }
                }
            }
        }
    }

    return 0;
}