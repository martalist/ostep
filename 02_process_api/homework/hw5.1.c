#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("reading x from child: %d\n", x);
        x += 50;
        printf("reading x from child: %d\n", x);
    } else {
        int wc = wait(NULL);
        printf("reading x from parent: %d\n", x);
        x++;
        printf("reading x from parent: %d\n", x);
    }
    return 0;
}
