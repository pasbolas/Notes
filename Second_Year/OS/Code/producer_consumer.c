#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFF_SIZE 10

char buffer[BUFF_SIZE];
int producerIndex = 0;
int consumerIndex = 0;

int Times;

// Semaphores
sem_t EmptyPositions;   // counts empty slots
sem_t FullPositions;    // counts full slots
sem_t BufferLock;       // mutex for buffer

// ---------------------------------------------------
//          INSERT FUNCTION  (PRODUCER)
// ---------------------------------------------------
void Insert(char item)
{
    printf("Producing %c ...\n", item);

    // P operations
    sem_wait(&EmptyPositions);   // wait for an empty slot
    sem_wait(&BufferLock);       // lock buffer

    // critical section
    buffer[producerIndex] = item;

    // increment producer index circularly
    producerIndex = (producerIndex + 1) % BUFF_SIZE;

    // V operations
    sem_post(&BufferLock);       // unlock buffer
    sem_post(&FullPositions);    // signal a full slot
}

// ---------------------------------------------------
//          PRODUCER THREAD
// ---------------------------------------------------
void* Prod(void* t)
{
    int i;

    for (i = 0; i < Times; i++)
    {
        Insert((char)('A' + (i % 26)));
    }

    pthread_exit(NULL);
    return NULL;
}

// ---------------------------------------------------
//          DELETE FUNCTION (CONSUMER)
// ---------------------------------------------------
void Delete()
{
    char item;

    // P operations
    sem_wait(&FullPositions);    // wait for available item
    sem_wait(&BufferLock);       // lock buffer

    // critical section
    item = buffer[consumerIndex];

    // increment consumer index circularly
    consumerIndex = (consumerIndex + 1) % BUFF_SIZE;

    // V operations
    sem_post(&BufferLock);       // unlock buffer
    sem_post(&EmptyPositions);   // signal an empty slot

    printf("Consuming letter %c ...\n", item);
}

// ---------------------------------------------------
//          CONSUMER THREAD
// ---------------------------------------------------
void* Consume(void* t)
{
    int i;
    for (i = 0; i < Times; i++)
    {
        Delete();
    }

    pthread_exit(NULL);
    return NULL;
}

// ---------------------------------------------------
//          MAIN PROGRAM
// ---------------------------------------------------
int main(int argc, char** argv)
{
    pthread_t idP, idC;
    int rc1, rc2;

    // check CLI args
    if (argc < 2)
    {
        printf("Usage: %s <Times>\n", argv[0]);
        exit(1);
    }

    Times = atoi(argv[1]);

    // init semaphores
    sem_init(&EmptyPositions, 0, BUFF_SIZE); // buffer empty initially
    sem_init(&FullPositions, 0, 0);
    sem_init(&BufferLock, 0, 1);

    // create producer thread
    rc1 = pthread_create(&idP, NULL, Prod, NULL);
    if (rc1)
    {
        printf("Thread creation failed: %d\n", rc1);
        exit(1);
    }

    // create consumer thread
    rc2 = pthread_create(&idC, NULL, Consume, NULL);
    if (rc2)
    {
        printf("Thread creation failed: %d\n", rc2);
        exit(1);
    }

    // synchronize threads (join them)
    pthread_join(idP, NULL);
    pthread_join(idC, NULL);

    // destroy semaphores
    sem_destroy(&FullPositions);
    sem_destroy(&EmptyPositions);
    sem_destroy(&BufferLock);

    printf("Exiting program\n");
    return 0;
}
