#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// here we can Customize signal handler function
// many possibilities, we can start new processes, fork , or open new file exec or many other things
void handle_sigint(int sig)
{
    printf("\nSignal number: %d \n", sig); // sig is the signal number
    printf("Caught SIGINT (signal %d).\n", sig);
    exit(0);
}

int main()
{
    // Set up signal handler for SIGINT, which is a standard Signal.
    // SIGNINT denotes Ctrl + C
    // syntax: void (*signal(int signum, void (*Handler)(int)))(int)
    if ((*signal(SIGINT, *handle_sigint) == SIG_ERR))
    {
        perror("signal"); // if signal does not works then, it throws the error
        exit(EXIT_FAILURE);
    }

    // Infinite loop to keep the program running
    while (1)
    {
        printf("Running... Press Ctrl+C to send SIGINT.\n");
        sleep(1); // to stop memory from getting full
    }

    return 0;
}
