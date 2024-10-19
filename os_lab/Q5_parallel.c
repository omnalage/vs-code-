#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// parallel execution is, when the parent will create all the child processes and wait for them all to finish execution.
int main()
{
    pid_t ppid = getppid(); // get the pid of the parent

    int n;
    printf("Enter the number of Child processes you want to create: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    { // creating n processes in parallel
        pid_t pid = fork();

        if (pid == 0)
        {
            printf("Child process Number: %d, PID = %d\n", i, getpid());
            sleep(2); // simulating some kind of work
            exit(0);
            // exit returns the status of the child process about how it terminated, successfully or failure, which is being caught by the parent process of wait(& status)
        }
        else if (pid < 0)
        {
            printf("Error forking the processes! \n");
            exit(1); // exit status signifying error
        }
    }

    wait(NULL);
    printf("This is the parent process! \n");
    printf("PID of Parent is: %d \n", getpid());

    printf("All the child processes executed correctly (in parallel).");

    return 0;
}