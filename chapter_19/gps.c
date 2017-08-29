#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#define SAMPLES 0x700000

int main(int argc, char *argv[]) 
{
    int ps = getpagesize();
    printf("page size is %d\n", ps);
    printf("%d\n", INT_MAX >> 4);
    printf("%d\n", 0x09000000);
    return 0;
}
