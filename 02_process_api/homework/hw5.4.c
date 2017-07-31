#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void run_execl();
void run_execle();
void run_execlp();
void run_execv();
void run_execvp();
void run_execvP();

int main(int argc, char *argv[])
{ 
    int rc = fork();
    if (rc < 0 ) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc ==0) {        // child (new process) executes this block
        printf("\nPreparing to call \"ls -a ..\"\n");
        /* run_execl(); */
        /* run_execle(); */
        /* run_execlp(); */
        /* run_execv(); */
        /* run_execvp(); */
        run_execvP();
    } else {                    // parent executes this block
        int wc = wait(NULL);    // wait until the child process finished, then print
        printf("\nFinished running \"ls -a ..\" from hw5.4.c\n\n");
    }
    return 0;
}

void run_execl()
{
    execl("/bin/ls", "ls", "-a", "..", NULL);  // runs word count
}

void run_execle()
{
    char *myargs[4];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = strdup("ls");
    myargs[2] = strdup("..");
    myargs[3] = NULL;           // marks end of array
    execle(myargs[0], myargs[1], myargs[2], myargs[3], myargs);  // runs word count
}

void run_execlp()
{
    execlp("/bin/ls", "ls", "-a", "..", NULL);  // runs word count
}

void run_execv()
{
    char *myargs[4];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("-a");
    myargs[2] = strdup("..");
    myargs[3] = NULL;           // marks end of array
    execvp(myargs[0], myargs);  // runs word count
}

void run_execvp()
{
    char *myargs[4];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("-a");
    myargs[2] = strdup("..");
    myargs[3] = NULL;           // marks end of array
    execvp(myargs[0], myargs);  // runs word count
}

void run_execvP()
{
    char *myargs[4];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("-a");
    myargs[2] = strdup("..");
    myargs[3] = NULL;           // marks end of array
    execvP(myargs[0], "/bin", myargs);  // runs word count
}
