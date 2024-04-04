#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int myFork() {
    pid_t pid;

    /* fork a child process */
    pid = fork(); //pid(p)>0: pid of child process; pid(c): 0
    if (pid < 0) { /* error occurred. Child starts here */
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) { /* child process */
        printf("20140653-child\n");
	printf("자식 프로세스의 PID: %d\n", getpid());; // child ≠ parent now
    }
    else { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL); // transit to wait state
	printf("부모 프로세스의 PID: %d\n", getpid());
        printf("20140653-Child Complete\n");
    }
    return 0;
}
