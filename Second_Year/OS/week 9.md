
### Threads

**their types**
- single thread
- multi thread

we use thread control block here instead of pcb, this allows os to emulate like the process is ran on  multiple processors

## Concurrently - not exactly running at same time (fake parallelism)

-- works on the same physical registers but one after the another
## Parallel - Exactly what it says


# Multithreading Examples

#### TCP Connection


# Note:

1. Each thread is private

Then he said all threads share same global and shared memory. What?

2. If one thread change a variable its visible to other threads aswell.


## Thread control block

Its parameters
1. Thread id
2. Thread State
3. CPU info
	1. Program Counter
	2. Register COntents
4. Priority
5. Points to parent thread
6. Points to child threads aswell <---- problem here, the parent process can fuck up the child processes if they finish first


## States

### 1.  Delay
put to sleep for CERTAIN amount of time

### 2. Block 
waiting for i/o to complete

### 3. Wait
wait till certain event takes places, can it be time, or i/o????


### Programming This Crap

#### Note  (put this extra parameter)

```bash
gcc -o test test.c -lpthread
```



##### The variables passed to pthread_create function

pthread_create returns int

#### Put them in the param order mentioned

```c
pthread_attr_t *thread <-- first param
*start_routine <-- third param
void *args <--- passed as an address with no associated data type <-- fourth param <-- kinda not needed all times
pthread_attr_t *attr <-- second param
```

to exit the threads
pthread_exit() <--- no specific thread was passed here how does it know which one to kill??




## Note

At the end of main function if we are working with thread we put pthread_exit(NULL)

the order on which the threads are made is not the one in which they willl be run.



so do os think that making a thread is faster than running it even tho it just prints???