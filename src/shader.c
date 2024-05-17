#include "shader.h"

void setMat4Uniform(ShaderID shader, const char *uniform, float *matrix) {
    int uniformLocation = glGetUniformLocation(shader, uniform);
    if (uniformLocation == -1)
        printf("Couldn't find uniform: %s\n", uniform);
    glUniformMatrix4fv(uniformLocation, 1, GL_TRUE, matrix);
}

void setVec3Uniform(ShaderID shader, const char *uniform, float *vector) {
    int uniformLocation = glGetUniformLocation(shader, uniform);
    if (uniformLocation == -1)
        printf("Couldn't find uniform: %s\n", uniform);
    glUniform3fv(uniformLocation, 1, vector);
}

const char* readFile(const char *filepath) {
    char *shader;

    FILE *file = fopen(filepath, "r");
    if (file == NULL)
        printf("%s failed to open.\n", filepath);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    file = fopen(filepath, "r");
    shader = malloc(size);
    fread(shader, 1, size - 1, file);
    shader[size - 1] = '\0';
    fclose(file);
    
    return shader;
}

ShaderID createShader(const char *vertexFilepath, const char *fragmentFilepath) {
    const char *vertexShader = readFile(vertexFilepath);
    const char *fragmentShader = readFile(fragmentFilepath);

    unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexID, 1, &vertexShader, NULL);
    glCompileShader(vertexID);
    glShaderSource(fragmentID, 1, &fragmentShader, NULL);
    glCompileShader(fragmentID);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        printf("Vertex shader \"%s\" compilation failed.\n%s\n", vertexFilepath, infoLog);
    };

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        printf("Fragment shader \"%s\" compilation failed.\n%s\n", fragmentFilepath, infoLog);
    };

    ShaderID id = glCreateProgram();
    glAttachShader(id, vertexID);
    glAttachShader(id, fragmentID);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        printf("Shader program \"%d\" linking failed.\n%s\n", id, infoLog);
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    free((void *)vertexShader);
    free((void *)fragmentShader);

    return id;
}
