#include <stdio.h>
#include <string.h>         // strcmp(), strcpy()
#include <stdlib.h>         // exit(), malloc(), realloc(), free()
#include <unistd.h>         // fork(), getpid(), exec(), chdir()
#include <sys/wait.h>       // wait()
#include <signal.h>         // signal()
#include <fcntl.h>          // close(), open()

void handle_sigint(int signo)
{
    // This function is for handling signals in the child process
    exit(0);
}

char** parseInput(char* string, int* choice, int* numOfArgs)
{
    // This function parses the input string into multiple commands or a single command with arguments depending on the delimiter (&&, ##, >, or spaces).
    int size = 1;
    for (int i = 1; i < strlen(string); ++i)
        if (string[i] == ' ') size += 1;

    char** parsedArgs = (char**)malloc(size * sizeof(char*));
    char *delimiter = " ";
    char *word;
    int length = 0;

    // Splits input string.
    word = strtok(string, delimiter);
    while (word != NULL)
    {
        parsedArgs[length] = word;  // Storing separated words in parsedArgs array.
        word = strtok(NULL, delimiter);
        length += 1;
    }

    if (parsedArgs[length - 1][strlen(parsedArgs[length - 1]) - 1] == '\n')
        parsedArgs[length - 1][strlen(parsedArgs[length - 1]) - 1] = '\0'; // Removing newline character read at the end

    char* exit = "exit";
    char* found0 = "&&";       // Different types of special commands or delimiters
    char* found1 = "##";
    char* found2 = ">";

    // Detecting the type of command, choice pointer stores the type of command

    if (strcmp(parsedArgs[0], exit) == 0 && size == 1) // Exit command
        *choice = -1;

    for (int i = 0; i < size; ++i) {
        if (strcmp(parsedArgs[i], found0) == 0) { // Parallel execution
            *choice = 0;
            break;
        }
        else if (strcmp(parsedArgs[i], found1) == 0) { // Sequential execution
            *choice = 1;
            break;
        }
        else if (strcmp(parsedArgs[i], found2) == 0) { // Output redirection
            *choice = 2;
            break;
        }
    }
    *numOfArgs = size;
    return parsedArgs; // Sending back split arguments
}

void executeCommand(char** execCommand, int size)
{
    // Check and execute for cd command
    if (strcmp(execCommand[0], "cd") == 0) {
        if (size == 2) {
            if (chdir(execCommand[1]) != 0) // Checking for successful run of command
                printf("cd: %s: No such file or directory\n", execCommand[1]);
        }
    }
    else {
        // This function forks a new process to execute a command

        execCommand = (char**)realloc(execCommand, (size + 1) * sizeof(char*)); // Adding NULL at the end for the execvp command
        execCommand[size] = NULL;

        int rc = fork();

        if (rc < 0) {            // Fork failed; exit
            exit(0);
        }
        else if (rc == 0) {      // Child (new) process
            signal(SIGINT, handle_sigint);

            //EXEC system call
            int retval = execvp(execCommand[0], execCommand);
            if (retval < 0) {
                printf("Shell: Incorrect command\n");
                exit(0);
            }
         
        }
        else {              // Parent process (rc holds child PID)
            wait(NULL); // Parent waits till child finishes
        }
    }
}

void executeParallelCommands(char** execCommands, int size)
{
    // This function runs multiple commands in parallel

    int i = 0, start = 0, j;
    while (start < size) {
        j = 0;
        char** tempCommands = (char**)malloc(10 * sizeof(char*)); // Array to hold individual commands

        // Getting individual commands between the delimiter
        for (i = start; i < size; ++i) {
            if (strcmp(execCommands[i], "&&") == 0) {
                start = i + 1;
                break;
            }
            tempCommands[j++] = execCommands[i];
        }
        tempCommands[j] = NULL;

        if (strcmp(tempCommands[0], "cd") == 0) {
            if (chdir(tempCommands[1]) != 0)
                printf("cd: %s: No such file or directory\n", tempCommands[1]);
        }
        else {
            int rc = fork();
            if (rc < 0) {            // Fork failed; exit
                exit(0);
            }
            else if (rc == 0) {      // Child (new) process
                signal(SIGINT, handle_sigint);

                // EXEC system call 
                execvp(tempCommands[0], tempCommands);
                printf("Shell: Incorrect command\n");
                exit(0);
              
            }
        }
        free(tempCommands);
        start = i + 1;
    }

    while (wait(NULL) > 0); // Parent waits for all child processes to finish
}

void executeSequentialCommands(char** execCommands, int size)
{
    // This function runs multiple commands in sequence

    int i = 0, start = 0, j;
    while (start < size) {
        j = 0;
        char** tempCommands = (char**)malloc(10 * sizeof(char*)); // Array to hold individual commands

        // Getting individual commands between the delimiter
        for (i = start; i < size; ++i) {
            if (strcmp(execCommands[i], "##") == 0) {
                start = i + 1;
                break;
            }
            tempCommands[j++] = execCommands[i];
        }
        tempCommands[j] = NULL;

        executeCommand(tempCommands, j);
        free(tempCommands);
        start = i + 1;
    }
}

void executeCommandRedirection(char** execCommands, int size)
{
    // This function runs a single command with output redirected to an output file specified by the user

    char** tempCommands = (char**)malloc(10 * sizeof(char*)); // Array to hold individual commands
    int i = 0, j = 0;

    // Extract the command and the redirection file
    for (i = 0; i < size; ++i) {
        if (strcmp(execCommands[i], ">") == 0) {
            tempCommands[j] = NULL;
            break;
        }
        tempCommands[j++] = execCommands[i];
    }

    int rc = fork();

    if (rc < 0) {            // Fork failed; exit
        exit(0);
    }
    else if (rc == 0) {      // Child (new) process
        //Redirecting STDOUT 
        int file_desc = open(execCommands[size - 1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU); // Opening user-specified file
        if (file_desc < 0) {
            printf("Error opening the file\n");
            exit(1);
        }
        dup2(file_desc, STDOUT_FILENO); // Temporarily replace STDOUT with the given file
        close(file_desc);

        
        execvp(tempCommands[0], tempCommands);
        printf("Shell: Incorrect command\n");
        exit(0);
    }
    else {              // Parent process (rc holds child PID)
        wait(NULL);
    }
    free(tempCommands);
}

int main()
{
    // Initial declarations
    signal(SIGINT, SIG_IGN); // Ignores Ctrl + C
    signal(SIGTSTP, SIG_IGN); // Ignores Ctrl + Z

    while (1)    // This loop keeps your shell running until the user exits.
    {
        // Print the prompt in the format - currentWorkingDirectory$
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s$", cwd);

        // Accept input with 'getline()'
        size_t size = 10;
        char* string = (char*)malloc(size);
        ssize_t bytes_read = getline(&string, &size, stdin);

        if (bytes_read != -1 && strlen(string) > 1) {

            // Parse input with 'strtok()' for different symbols (&&, ##, >) and for spaces.
            int choice = 3, numOfArgs = 0;
            char** command = parseInput(string, &choice, &numOfArgs);

            if (choice == -1)    // When user uses exit command.
            {
                printf("Exiting shell...\n");
                free(string);
                break;
            }

            if (choice == 0)
                executeParallelCommands(command, numOfArgs);        // This function is invoked when user wants to run multiple commands in parallel (commands separated by &&)
            else if (choice == 1)
                executeSequentialCommands(command, numOfArgs);
            else if (choice == 2)
                executeCommandRedirection(command, numOfArgs);    // This function is invoked when user wants to redirect output of a single command to a file specified by user
            else
                executeCommand(command, numOfArgs);        // This function is invoked when user wants to run a single command

            // Free the memory allocated for command arguments
            free(command);
        }

        // Free the memory allocated for input string
        free(string);
    }

    return 0;
}
