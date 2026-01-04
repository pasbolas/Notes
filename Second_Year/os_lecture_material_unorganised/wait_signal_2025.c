/******************************************************************************
* FILE: condvar.c
* DESCRIPTION:
*   Example code for using Pthreads condition variables.  The main thread
*   creates three threads.  Two of those threads increment a "count" variable,
*   while the third thread watches the value of "count".  When "count" 
*   reaches a predefined limit, the waiting thread is signaled by one of the
*   incrementing threads. The waiting thread "awakens" and then modifies
*   count. The program continues until the incrementing threads reach
*   TCOUNT. The main program prints the final value of count.
* SOURCE: Adapted from example code in "Pthreads Programming", B. Nichols
*   et al. O'Reilly and Associates. 
* LAST REVISED: 10/14/10  Blaise Barney
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define NUM_THREADS  3
#define TCOUNT 6
#define COUNT_LIMIT 10 

int  count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *signal_fnt(void *t) 
{
  int i;
  long my_id = (long)t;
  printf("Signal thread id %ld is starting...", my_id);
  for (i=0; i < TCOUNT; i++) {
    pthread_mutex_lock(&count_mutex);
    count++;

    /* 
    Check the value of count and signal waiting thread when condition is
    reached.  Note that this occurs while mutex is locked. 
    */
    if (count == COUNT_LIMIT) {
      printf("thread %ld, count = %d  Threshold reached. ",
             my_id, count);
      pthread_cond_signal(&count_threshold_cv);
      printf("Just sent signal to waiting thread.\n");
      }
    printf("thread %ld, count = %d, unlocking mutex\n", 
	   my_id, count);
    pthread_mutex_unlock(&count_mutex);

    /* Do some work so threads can alternate on mutex lock */
    sleep(1);
    }
  pthread_exit(NULL);
}

void *wait_fnt(void *t) 
{
  long my_id = (long)t;

  printf("Starting wait thread: thread ID is:  %ld\n", my_id);

  pthread_mutex_lock(&count_mutex);
  while (count < COUNT_LIMIT) {
	printf("In wait thread %ld Count= %d. Going into wait state...\n", my_id,count);
		
	pthread_cond_wait(&count_threshold_cv, &count_mutex);  
	printf("thread %ld Condition signal received. Count= %d\n", my_id,count);
	printf("thread %ld Updating the value of count %d...\n", my_id,count);
		
    count += 200;

	printf("thread %ld count now = %d .\n", my_id, count);
    }
  
  printf("thread %ld Unlocking mutex.\n", my_id);
 
  pthread_mutex_unlock(&count_mutex);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  int i, rc; 
  long t1=7, t2=2, t3=10;
  pthread_t threads[3];
  pthread_attr_t attr;

  pthread_mutex_init(&count_mutex, NULL);
  pthread_cond_init (&count_threshold_cv, NULL);

  
  pthread_create(&threads[0], NULL, wait_fnt, (void *)t1);
  pthread_create(&threads[1], NULL, signal_fnt, (void *)t2);
  pthread_create(&threads[2], NULL, signal_fnt, (void *)t3);

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("Wait and signal theads finished Final value of count = %d!!!\n", 
          count);

  /* Clean up and exit */

  pthread_mutex_destroy(&count_mutex);
  pthread_cond_destroy(&count_threshold_cv);
  
  pthread_exit (NULL);

}


