#include "window.h"
#include "linalg.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    (void)window;
}

void processInput(GLFWwindow *window, Camera *camera) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->position = vec3Add(vec3ScalarMutliply(camera->front, camera->speed), camera->position);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->position = vec3Subtract(camera->position, vec3ScalarMutliply(camera->front, camera->speed));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->position = 
            vec3Subtract(camera->position,
                         vec3ScalarMutliply(normalizeVec3(crossVec3(camera->front, camera->up)), camera->speed));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->position =
            vec3Add(vec3ScalarMutliply(normalizeVec3(crossVec3(camera->front, camera->up)), camera->speed), camera->position);
}
