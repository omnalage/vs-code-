/*  primes module
 *  Primary module providing control flow for the primes program
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "counter.h"
#include "primes.h"
#define OUTPUT 1

counter_t primessearch;
counter_t primescnt;
int genprimes = 1000;
int nth_prime = 0;
pthread_mutex_t nth_lock;
pthread_cond_t nth_cond;

bool findPrime(int threadid)
{
  int n = inc_counter(&primessearch);
  int halfOfn = n / 2;
  for (int i = 2; i <= halfOfn; i++)
  {
    if (n % i == 0)
    {
      return false;
    }
  }

#if OUTPUT
  pthread_mutex_lock(&nth_lock);
  if (nth_prime < genprimes)  // Only print if we haven't reached the limit
  {
    switch (threadid)
    {
      case 1:
        printf("\033[0;31m%d,", n);
        break;
      case 2:
        printf("\033[0;32m%d,", n);
        break;
      case 3:
        printf("\033[0;33m%d,", n);
        break;
      case 4:
        printf("\033[0;34m%d,", n);
        break;
      case 5:
        printf("\033[0;35m%d,", n);
        break;
      case 6:
        printf("\033[0;36m%d,", n);
        break;
      case 7:
        printf("\033[1;32m%d,", n);
        break;
      case 8:
        printf("\033[1;34m%d,", n);
      case 9:
        printf("\033[1;33m%d,", n); 
    }
    nth_prime++;
    if (nth_prime >= genprimes)  // Signal when we reach the target
    {
      pthread_cond_broadcast(&nth_cond);  // Wake up all threads
    }
  }
  pthread_mutex_unlock(&nth_lock);
#endif
  usleep(100);
  inc_counter(&primescnt);
  return true;
}

void *generatePrimes(void *threadid)
{
  while (1)
  {
    pthread_mutex_lock(&nth_lock);
    if (nth_prime >= genprimes)  // Check if we've reached the target
    {
      pthread_mutex_unlock(&nth_lock);
      break;  // Stop the thread if the target is reached
    }
    pthread_mutex_unlock(&nth_lock);

    findPrime((int)(size_t)threadid);  // Continue finding primes
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t p1, p2, p3, p4, p5, p6, p7, p8;
  init_counter(&primessearch);
  init_counter(&primescnt);

  if (argc == 2)
    genprimes = atoi(argv[1]);

  pthread_mutex_init(&nth_lock, NULL);
  pthread_cond_init(&nth_cond, NULL);

  pthread_create(&p1, NULL, generatePrimes, (void *)(size_t)1);  // Thread 1
  pthread_create(&p2, NULL, generatePrimes, (void *)(size_t)2);  // Thread 2
  pthread_create(&p3, NULL, generatePrimes, (void *)(size_t)3);  // Thread 3
  pthread_create(&p4, NULL, generatePrimes, (void *)(size_t)4);  // Thread 4
  pthread_create(&p5, NULL, generatePrimes, (void *)(size_t)5);  // Thread 5
  pthread_create(&p6, NULL, generatePrimes, (void *)(size_t)6);  // Thread 6
  pthread_create(&p7, NULL, generatePrimes, (void *)(size_t)7);  // Thread 7
  pthread_create(&p8, NULL, generatePrimes, (void *)(size_t)8);  // Thread 8

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  pthread_join(p5, NULL);
  pthread_join(p6, NULL);
  pthread_join(p7, NULL);
  pthread_join(p8, NULL);

  pthread_mutex_destroy(&nth_lock);
  pthread_cond_destroy(&nth_cond);

  printf("\b \n");

  return 0;
}