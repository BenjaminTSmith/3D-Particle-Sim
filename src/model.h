#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    float *array;
} Array;

Array instantiate(size_t capacity);
void push(Array *, float);
void clean(Array *);

#endif // !MODEL_H
