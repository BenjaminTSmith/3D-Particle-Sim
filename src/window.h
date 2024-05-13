#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

#include "camera.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Camera *camera);

#endif // !WINDOW_H
