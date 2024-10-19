#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int readersCount;    // Number of readers arrived
int writersCount;    // Number of writers arrived


sem_t Rlock;         // Lock for readers, which will also be used by writer to block all incoming readers
sem_t writelock;     // Mutex for writers
sem_t readlock;      // Mutex for readers
sem_t resource;      // Mutex for managing critical section (i.e. only 1 write at a time)

void *readerThread(void *number) 
{
    int execTime = *(int *)number;
    time_t curtime;
    
    // Wait for writers to finish before readers can proceed
    sem_wait(&Rlock);
    
    // Increment readers count
    sem_wait(&readlock);
    readersCount++;
    if (readersCount == 1) {
        sem_wait(&resource);  // First reader locks the resource
    }
    sem_post(&readlock);
    sem_post(&Rlock);

    // Reading
    curtime = time(NULL);
    printf("%sReader is reading for %d seconds.\n\n", asctime(localtime(&curtime)), execTime);
    sleep(execTime);
        
    // Decrement readers count and release the resource if no readers are left
    sem_wait(&readlock);
    readersCount--;
    if (readersCount == 0) {
        sem_post(&resource);  // Last reader releases the resource
    }
    sem_post(&readlock);
}

void *writerThread(void *number) 
{
    int execTime = *(int *)number;
    time_t curtime;

    // Increment writers count and block readers
    sem_wait(&writelock);
    writersCount++;
    if (writersCount == 1) {   // First writer blocks readers
        sem_wait(&Rlock);
    }
    sem_post(&writelock);

    // Writing
    sem_wait(&resource);  // Lock the resource

    curtime = time(NULL);
    printf("%sWriter is writing for %d seconds.\n\n", asctime(localtime(&curtime)), execTime);
    sleep(execTime);

    sem_post(&resource);  // Free the resource
    
    // Decrement writers count and unblock readers if no writers are left
    sem_wait(&writelock);
    writersCount--;
    if (writersCount == 0) {  // Last writer releases Rlock
        sem_post(&Rlock);
    }
    sem_post(&writelock);
}

int main() 
{
    pthread_t tid[9];
    
    int i;
    int Number[9];
    time_t curtime;
    
    // Initialize the numbers array with execution times of threads
    Number[0] = 8;
    Number[1] = 6;
    Number[2] = 5;
    Number[3] = 6;
    Number[4] = 2;
    Number[5] = 2;
    Number[6] = 4;
    Number[7] = 2;
    Number[8] = 3;
    
    // Initialize the semaphores and counters with initial values
    sem_init(&Rlock, 0, 1);
    sem_init(&readlock, 0, 1);
    sem_init(&writelock, 0, 1);
    sem_init(&resource, 0, 1);
    writersCount = 0;
    readersCount = 0;
    
    curtime = time(NULL);
    printf("%sStarting program execution.\n\n", asctime(localtime(&curtime)));
    
    // Create the readers and writers.
    pthread_create(&tid[0], NULL, readerThread, &Number[0]);
    sleep(2);
    pthread_create(&tid[1], NULL, readerThread, &Number[1]);
    sleep(2);
    pthread_create(&tid[2], NULL, readerThread, &Number[2]);
    sleep(1);
    pthread_create(&tid[3], NULL, writerThread, &Number[3]);
    sleep(1);
    pthread_create(&tid[4], NULL, readerThread, &Number[4]);
    sleep(1);
    pthread_create(&tid[5], NULL, readerThread, &Number[5]);
    pthread_create(&tid[6], NULL, writerThread, &Number[6]);
    sleep(1);
    pthread_create(&tid[7], NULL, readerThread, &Number[7]);
    sleep(1);
    pthread_create(&tid[8], NULL, readerThread, &Number[8]);

    // Join each of the threads to wait for them to finish.
    for (i = 0; i < 9; i++) 
        pthread_join(tid[i], NULL);

    curtime = time(NULL);
    printf("%sCompleted program execution.\n\n", asctime(localtime(&curtime)));
}