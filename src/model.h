#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linalg.h"

#define VERTEX_LIMIT 5000

typedef struct {
    size_t size;
    size_t capacity;
    float *array;
} Array;

typedef struct {
    unsigned int VAO, VBO, vertexCount;
} Mesh;

typedef struct {
    Mesh mesh;
    mat4 model;
} Model;

Array instantiateArray(size_t capacity);
void push(Array *, float);
void clean(Array *);

Array readOBJ(const char *);
Mesh createMesh(const char *);
Model createModel(Mesh, mat4);

#endif // !MODEL_H
