#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int a = 5;

    pid_t pid = getpid();

    printf("This is parent process running!\n");
    printf("PID of parent : %d \n", pid);

    char *args[] = {"./random_file", NULL};
    execv(args[0], args);

    printf("BACK TO MAIN PROCESS THREAD!"); // this will not be executed if everything goes right.

    return 0;
}