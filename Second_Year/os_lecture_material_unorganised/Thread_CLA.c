#include<pthread.h>
#include <stdio.h>
#include<stdlib.h>


/*   ************************************************************   */
/* Example program creating thread to compute square of value       */
/*  Jogn Gilligan notes: Threads and processes                      */
/* **************************************************************** */
 


int value;/* thread stores result here */
void *my_thread(void *param);		  /* the thread */

int main (int argc, char *argv[])
{
	pthread_t tid;		/* thread identifier */
	int retcode;

	/* check input parameters */
	if (argc != 4) {
		printf ("number of command line must be 4\n");
		exit(0);
	}



/* create the thread */

	retcode = pthread_create(&tid,NULL,my_thread,argv[2]);
	if (retcode != 0) {
		fprintf (stderr, "Unable to create thread\n");
		exit (1);
	}

	/* wait for created thread to exit */
	pthread_join(tid,NULL);
	printf ("The value returned by the child thread is %d\n", value);
	printf("exiting program");

	return(0);
} //main

/* The thread will begin control in this function */

void *my_thread(void *Child)
{

        
	int i = atoi(Child);

	printf ("I am the child thread and was passed value %d\n", i);
	value = i*i*i;

	/* next line is not really necessary */
	pthread_exit(0);
}



