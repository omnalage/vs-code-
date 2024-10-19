#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int a = 3;

    pid_t pid = fork();

    if (pid > 0)
    {
        printf("\n PID of Child : %d \n \n", pid);
        wait(0); // used to terminate parent process until child completes it's execution

        printf("Parent process printed! \n");
        printf("%d \n", a);
    }
    else
    {
        printf("Child Process printed! \n");
        printf("%d \n", a);
    }

   return 0;
}