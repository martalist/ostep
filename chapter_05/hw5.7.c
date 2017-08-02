#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* #include <string.h> */
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{ 
    int rc = fork();
    if (rc < 0 ) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc ==0) {        // child: redirect stdout to a file
        printf("Preparing to close standard output (STDOUT_FILENO)...\n\n");
        close(STDOUT_FILENO);
        printf("Let's try to print after closing the descriptor\n");
    } else {                    // parent executes this block
        int wc = wait(NULL);    // wait until the child process finished, then print
        printf("My work here is done.\n\t\t~ Parent\n");
    }
    return 0;
}
