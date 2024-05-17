#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned int ShaderID;

const char *readFile(const char *);
ShaderID createShader(const char *, const char *);

void setMat4Uniform(ShaderID, const char *, float *);
void setVec3Uniform(ShaderID, const char *, float *);

#endif // !SHADER_H
