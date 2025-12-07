/* ----------------------------------------------------------------- */
/* PROGRAM fork-04.c                                                 */
/*    This one is modification of for4.c                             */
/* process also does some computation.                               */
/* ----------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void ChildProcess1(int);      /* child process prototype  */
void ParentProcess(char *);   /* parent process prototype */

int main(int argc, char **argv)
{
     pid_t pid1, pid;
     int status;
     int value;

     if (argc != 2) {
          printf("incorrect number of arguments, exit program\n");
          exit(0);
     }

     printf("*** Parent is about to fork process 1 ***\n");
     
     // any code after this will be executed by both parent and child
     pid1 = fork();

     // the child will get the pid1 = 0, parent will get pid1 > 0
     // two instances of pid1 exist now

     if (pid1 < 0) 
     {
        printf("Failed to fork process 1\n");
        exit(1);
     } 
     else if (pid1 == 0) 
     {
          value = atoi(argv[1]);
          ChildProcess1(value);
     }

     // pid is assigned the process ID of the terminated child
    pid = wait(&status);

    printf("*** Parent enters waiting status .....\n");
    printf("*** Parent detects process %d was done ***\n", pid);
    
    ParentProcess(argv[1]);
    printf("\n*** Parent exits ***\n");

    return 0;
}

/* ----------------------------------------------------------------- */
/* FUNCTION  ParentProcess :                                         */
/*    This function displays the first command line argument         */
/* ----------------------------------------------------------------- */

void ParentProcess(char *string)
{
    printf("\nParent process output: The first commandline argument is %s\n", string);
}

/* ----------------------------------------------------------------- */
/* FUNCTION  ChildProcess1 :                                         */
/*    This function computes the square of second commandline arg    */
/* ----------------------------------------------------------------- */

void ChildProcess1(int value)
{
     pid_t pid;
     
     pid = getpid();
     printf("child process 1 starts (pid = %d)\n", pid);
     printf("\nthe square of the second commandline argument is = %d;\n" 
          "Exit child process\n",
               value * value);

     exit(0);
}