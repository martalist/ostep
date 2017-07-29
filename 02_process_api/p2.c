#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{ 
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0 ) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc ==0) {        // child (new process) executes this block
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {                    // parent executes this block
        int wc = wait(NULL);    // wait until the child process finished, then print
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", 
                rc, wc, (int) getpid());
    }
    return 0;
}
