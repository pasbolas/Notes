/* program found at:

	to pass coomand line arguments to a c program

	this will pass the second argument to the child process
	the third argumeny to the parent process



*/


#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
    printf("--beginning of program\n");

   if (argc != 3) {
	printf("number of command line arguments should be 3\n");
	printf("exiting program......\n");	
	exit(0);
    }


    int counter = 0;
    int second;
    
    pid_t pid = fork();

    if (pid == 0)
    {
        // child process

	
	int max_c = atoi(argv[1]);   

	printf("the second argument is %s\n",argv[1]);
        int i,x;
        for (i = 0; i < 5; ++i)
        {
            printf("child process: counter=%d\n", ++counter);
            for(x=0; x<max_c;x++);		
        }
    }
    else if (pid > 0)
    {
        // parent process
        int j,x, status;
	
	int  max_p = atoi(argv[2]);

	printf("the third argument is %s\n",argv[2]);
	//pid = wait(&status);
        for (j=0; j < 5; ++j)
	{
            printf("parent process: counter=%d\n", ++counter);
	    for (x=0;x<max_p;x++);	
        }
    }
    else
    {
        // fork failed
        printf("fork() failed!\n");
        return 1;
    }

    printf("--end of program--\n");

    return 0;
}


