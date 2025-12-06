        /*  this code was found at forum:
		
			http://ubuntuforums.org/showthread.php?t=609975
			
			compile with gcc -o semaphore_example semaphore_example.c -pthread -lrt
			
		*/
		
		
		#include <unistd.h>
        #include <stdio.h>
        #include <string.h>
        #include <pthread.h>
        #include <semaphore.h>

        sem_t sem1, sem2;

        void *thread1( void *arg ) 
        {
            int value;	
            sem_getvalue(&sem1, &value); 
            printf("Start Thread1: The value of semaphore 1 is %d\n", value);

            sem_getvalue(&sem2,&value);
            printf("Start Thread 1: The value of semaphore 2 is %d\n",value);
        
            sem_wait( &sem1 );
            printf( "I'm in thread 1,signal sem2\n" );
            sem_post( &sem2 );
        
            sem_getvalue(&sem1, &value); 
            printf("End Thread 1: The value of semaphore 1 is now %d\n", value);

            sem_getvalue(&sem2, &value); 
            printf("End Thread 1: The value of semaphore 2 is now %d\n", value);


            pthread_exit( NULL );
            return NULL;
        }

        void *thread2( void *arg ) 
        {
            int value;

            sem_getvalue(&sem1, &value); 
            printf("Start Thread 2: The value of semaphore 1 is %d\n", value);

	        sem_getvalue(&sem2,&value);
	        printf("Start Thread 2: The value of semaphore 2 is %d\n",value);
	   
	        sem_wait( &sem2 );
            printf( "I'm in thread 2, awoken by thread 1\n" );
         
	        sem_getvalue(&sem1, &value); 
            printf("End Thread 2: The value of semaphore 1 is now %d\n", value);

	        sem_getvalue(&sem2, &value); 
            printf("End Thread 2: The value of semaphore 2 is now %d\n", value);
	
            pthread_exit( NULL );
            return NULL;
        }



        int main( int argc, char **argv ) 
        {
           
            /* initalise the semaphores (mutex) the first is free
			the second (set to 0) is busy: ensure thread 1 is executed before thread 2*/
	        sem_init( &sem1, 0, 1 );
            sem_init( &sem2, 0, 0 );

            pthread_t threads[ 2 ]; 

            // Thread 2 is run first
            pthread_create( &threads[ 0 ], NULL, thread2, NULL );
            sleep( 1 );
            pthread_create( &threads[ 1 ], NULL, thread1, NULL );

           
	        /* prevents process from closing before threads are executed */
            pthread_join( threads[ 0 ], NULL );
            pthread_join( threads[ 1 ], NULL );


            sem_destroy( &sem2 );
            sem_destroy( &sem1 );

            return 0;
        }

   

