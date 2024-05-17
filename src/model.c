#include "model.h"

Array instantiate(size_t capacity) {
    Array array;
    array.size = 0;
    array.capacity = capacity;
    array.array = malloc(sizeof(float) * capacity);
    return array;
}

void push(Array *array, float value) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->array = (float *)realloc(array->array, sizeof(float) * array->capacity);
    }
    array->array[array->size] = value;
    array->size++;
}

void clean(Array *array) {
    free(array->array);
}
