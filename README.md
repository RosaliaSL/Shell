# Shell

A simple shell that handles three internal commands – ‘cd’, ‘echo’ and ‘pwd’ and five external commands – ‘ls’, ‘cat’, ‘date’, ‘rm’ and ‘mkdir’. 

External commands have been handled using two methods.
- Creating a new process using the fork() system call and using the execvp()call to run the individual program for the external command.
External commands have been handled by creating a new process, using the fork() system ‘call and within each process you need to use the execl() family system call to run the individual program. 
The parent program must also wait for the child program to terminate using the wait() family of system calls.
For each of these commands, you need not handle all the command line options. Two options per command is sufficient. You need to document which two options you are handling and need to demonstrate correct func- tioning of the command with respect to (atleast) your chosen options. You also need to handle corner cases such as invalid options (graceful degra- dation).

2. The second task would be the achieve the above functionality of the shell using pthread create() (instead of fork()) and system() (instead of
1
execl() family of functions). The thread based execution would be per- formed if the command is followed by the characters, “&t”. The rest of the functionalities should remain the same. Note: you only need one set of external command programs which could be used with either versions of the shell, be it the that uses fork()/execl() or the one that uses pthread create()/system().
