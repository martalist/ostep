#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE* file = fopen("new_file.output", "a");
    if (file == NULL) {
        fprintf(stderr, "\n fopen() failed");
    } else {
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            fclose(file);
            exit(1);
        } else if (rc == 0) {
            for (int i=0; i<5; i++) 
                fprintf(file, "writing from child, #%d\n", i);
        } else {
            /* int wc = wait(NULL); */
            for (int i=0; i<5; i++) 
                fprintf(file, "writing from parent, #%d\n", i);
        }
        fclose(file);
    }
    return 0;
}
