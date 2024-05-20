#include "mesh.h"

Array instantiateArray(size_t capacity) {
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

Array readOBJ(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file)
        printf("Failed to open %s.\n", filename);
    vec3 v[VERTEX_LIMIT];
    int vCount = 0;
    vec2 vt[VERTEX_LIMIT];
    int vtCount = 0;
    vec3 vn[VERTEX_LIMIT];
    int vnCount = 0;
    Array vertices = instantiateArray(100);

    char *line;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        char* tokens[4];
        tokens[0] = strtok(line, " ");
        tokens[1] = strtok(NULL, " ");
        tokens[2] = strtok(NULL, " ");
        tokens[3] = strtok(NULL, " ");
    
        if (!strcmp(tokens[0], "v")) {
            v[vCount].x = atof(tokens[1]);
            v[vCount].y = atof(tokens[2]);
            v[vCount].z = atof(tokens[3]);
            vCount++;
        } else if (!strcmp(tokens[0], "vt")) {
            vt[vtCount].x = atof(tokens[1]);
            vt[vtCount].y = atof(tokens[2]);
            vtCount++;
        } else if (!strcmp(tokens[0], "vn")) {
            vn[vnCount].x = atof(tokens[1]);
            vn[vnCount].y = atof(tokens[2]);
            vn[vnCount].z = atof(tokens[3]);
            vnCount++;
        } else if (!strcmp(tokens[0], "f")) {
            for (int i = 1; i < 4; i++) {
                int indices[3];
                indices[0] = atof(strtok(tokens[i], "/"));
                indices[1] = atof(strtok(NULL, "/"));
                indices[2] = atof(strtok(NULL, "/"));
                push(&vertices, v[indices[0] - 1].x);
                push(&vertices, v[indices[0] - 1].y);
                push(&vertices, v[indices[0] - 1].z);
                push(&vertices, vt[indices[1] - 1].x);
                push(&vertices, vt[indices[1] - 1].y);
                push(&vertices, vn[indices[2] - 1].x);
                push(&vertices, vn[indices[2] - 1].y);
                push(&vertices, vn[indices[2] - 1].z);
            }
        }
    }

    return vertices;
}

Mesh createMesh(const char *filename) {
    Mesh mesh;
    Array vertices = readOBJ(filename);
    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    glGenBuffers(1, &mesh.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size, vertices.array, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    mesh.vertexCount = vertices.size / 6;

    clean(&vertices);
    return mesh;
}
