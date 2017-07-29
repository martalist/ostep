#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{ 
    int rc = fork();
    if (rc < 0 ) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc ==0) {        // child: redirect stdout to a file
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        //now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p3.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
    } else {                    // parent executes this block
        int wc = wait(NULL);    // wait until the child process finished, then print
    }
    return 0;
}
