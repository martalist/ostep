#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int *data = (int *) malloc(100 * sizeof(int));
    *data = 100;
    free(data);
    printf("Trying to print freed data: %d\n", *data);
    return 0;
}
