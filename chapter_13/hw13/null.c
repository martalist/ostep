#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int *ptr = NULL;
    printf("dereferencing a NULL pointer: %d\n", *ptr);
}
