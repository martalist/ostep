#include <stdio.h>
#include <stdlib.h>

typedef struct vect {
    int *data;
    size_t length;
    size_t population;
} Vector;

Vector *new_vector(size_t length);
void delete(Vector *v);
void add(Vector *v, int elem);
int get(Vector *v, int index);

int main(int argc, char *argv[])
{
    Vector *vector = new_vector(0);
    if (vector == NULL) 
        return EXIT_FAILURE;

    printf("Vector has %d spaces and %d items stored\n", 
            (int) vector->length, (int) vector->population);
    
    add (vector, 5);
    printf("Vector has %d spaces and %d items stored\n", 
            (int) vector->length, (int) vector->population);

    printf("The value at index %d is %d\n", 
            0, vector->data[0]);
    delete(vector);
    return 0;
}

Vector *new_vector(size_t length)
{
    Vector *v = (Vector *) malloc(sizeof(Vector));
    if (v == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return NULL;
    }
    v->length = length;
    v->population = 0;
    v->data = (int *) calloc(length, sizeof(int));
    if (v->data == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return NULL;
    }
    return v;
}

void delete(Vector *v)
{
    free(v->data);
    free(v);
}

void add(Vector *v, int elem) 
{
    if (v->population >= v->length) { // need more space
        v->data = realloc(v->data, (v->length + 1) * sizeof(int));
        v->length++;
    }
    *(v->data + v->population++) = elem;
}

int get(Vector *v, int index)
{
    return v->data[index];
}
