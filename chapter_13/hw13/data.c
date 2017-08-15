#include <stdlib.h>

int main(int argc, char *argv[])
{
    int *data = (int *) malloc(100 * sizeof(int));
    data[100] = 0;
    return 0;
}
