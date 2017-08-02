#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    pid_t cpid = fork();
    if (cpid == -1) {
        fprintf(stderr, "child fork failure\n");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {        // child process
        int pipefd[2];
        char buf;

        if (pipe(pipefd) == -1) {
            fprintf(stderr, "pipe failure\n");
            exit(EXIT_FAILURE);
        }

        pid_t gcpid = fork();   // create grandchild process
        if (gcpid == -1) {
            fprintf(stderr, "grandchild fork failure\n");
            exit(EXIT_FAILURE);
        }

        if (gcpid == 0) {       // grandchild process reads from pipe
            close(pipefd[1]);   // close unused write end

            while (read(pipefd[0], &buf, 1) > 0)
                write(STDOUT_FILENO, &buf, 1);

            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);
            _exit(EXIT_SUCCESS);

        } else {

            char *text = "hello there, child!\n";
            close(pipefd[0]);   // close unused read end
            write(pipefd[1], text, strlen(text));
            close(pipefd[1]);   // Reader will see EOF
            wait(NULL);         // Wait for child
            exit(EXIT_SUCCESS);

        }

    } else {                // Parent writes text to text
        wait(NULL);         // Wait for child
        exit(EXIT_SUCCESS);
    }
}

