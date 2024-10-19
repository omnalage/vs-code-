#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t pid = getpid();
    printf("This is the random file that is opened by Execv! \n");
    printf("The process ID of this file opened is: %d \n", pid);
    return 0;
}
