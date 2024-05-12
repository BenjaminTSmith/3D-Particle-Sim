#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int ShaderID;

const char *readFile(const char *);
ShaderID createShader(const char *, const char *);

#endif // !SHADER_H
