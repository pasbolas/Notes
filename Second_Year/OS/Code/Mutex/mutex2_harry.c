/* 
    edited version of denis''s first mutex2 file
*/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void* doSomeThing()
{
    unsigned long i = 0;

    //mutex is locked
    pthread_mutex_lock(&mutex1);

    printf("--MUTEX LOCKED--\n");

    

    printf("\n Job %d started\n", counter);

    counter += 1;

    pthread_mutex_unlock(&mutex1);

    for(i=0; i<(0xFFFFFFFF);i++);

    printf("\n Job %d finished\n", counter);
    printf("--MUTEX UNLOCKED--\n");
    return NULL;
}

int main(void)
{
    int i = 0;
    int err;
    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}