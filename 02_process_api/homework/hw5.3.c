#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) 
{
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Failed to fork\n");
        exit(1);
    } else if (rc == 0) {
        printf("\nhello\n");
    } else {
        time_t timer, delay;
        time(&timer);   // get current time
        delay = timer + .01;
        while (difftime(delay, timer) >= 0)
            time(&timer);
        printf("goodbye\n\n");
    }
    return 0;
}
