#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// serial execution is, the parent waits for all the child process to complete execution before creating a new child

int main()
{
    pid_t ppid = getppid();

    int n;
    printf("Enter the number of Child processes you want to create: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("Child number: %d Created. \n", i);
            sleep(2); // sleep is function that makes the code sleep for n seconds, simulating some kind of work being done
            exit(0);
            // exit returns the status of the child process about how it terminated, successfully or failure, which is being caught by the parent process of wait(& status)
        }
        else if (pid > 0)
        {
            // this is the parent process
            wait(0);
            // here we could've also written wait(NULL), which signifies that we don't care about how the child exited.
            printf("This is the parent process! \n");

            // this part could be removed, redundant. but to show that, the children belong to the same parent.
            printf("The process ID of this Child %d is: %d \n", i, pid);
            printf("Process ID of parent is: %d \n \n", ppid);
        }
        else
        {
            printf("Error forking the processes! \n");
            exit(1); // exit status signifying error
        }
    }

    printf("All the child processes executed correctly (serially).");

    return 0;
}
