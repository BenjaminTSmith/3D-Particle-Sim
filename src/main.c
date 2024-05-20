#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "linalg.h"
#include "camera.h"
#include "shader.h"
#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1600, 900, "Particle Sim", NULL, NULL);
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    if (err != GLEW_OK && err != 4) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glViewport(0, 0, 1600, 900);

    ShaderID shaderProgram = createShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    ShaderID sphereProgram = createShader("shaders/sphere_vertex.glsl", "shaders/lighting.glsl");

    Mesh sphereMesh = createMesh("models/sphere.obj");
    Model sphere = createModel(sphereMesh, identityMatrix);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sphereMesh.VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.12, 0.1, 0.11, 1.0);

    Camera camera;
    vec3 position = {{ 0, 0, 3 }};
    vec3 front = {{ 0, 0, -1 }};
    vec3 up = {{ 0, 1, 0 }};
    camera.position = position;
    camera.front = front;
    camera.up = up;
    camera.speed = 0.05;

    float delta = 0;
    float lastFrame = 0;

    vec3 origin = {{ 0, 0, 0 }};

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);

        float frame = glfwGetTime();
        delta = frame - lastFrame;
        lastFrame = frame;
        (void)delta;

        camera.position.x = sin(glfwGetTime() / 2) * 5;
        camera.position.z = cos(glfwGetTime() / 2) * 5;
        camera.front = normalizeVec3(vec3Subtract(origin, camera.position));


        mat4 view = lookAt(camera.position, vec3Add(camera.front, camera.position), camera.up);
        mat4 projection = perspective(PI / 4, 16. / 9., 0.1, 100);
        vec3 lightPos = {{ sin(glfwGetTime()) * 2, 1, cos(glfwGetTime()) * 2 }};
        vec3 lightScale = {{ 0.1, 0.1, 0.1 }};
        mat4 lightModel = scale(identityMatrix, lightScale);
        lightModel = translate(lightModel, lightPos);
        vec3 lightColor = {{ 1, 1, 1 }};
        vec3 objectColor = {{ 1, 0, 0 }};

        glUseProgram(sphereProgram);
        mat4 model = identityMatrix;
        setMat4Uniform(sphereProgram, "model", model.mat);
        setMat4Uniform(sphereProgram, "view", view.mat);
        setMat4Uniform(sphereProgram, "projection", projection.mat);
        setVec3Uniform(sphereProgram, "lightPos", lightPos.vec);
        setVec3Uniform(sphereProgram, "lightColor", lightColor.vec);
        setVec3Uniform(sphereProgram, "objectColor", objectColor.vec);

        glBindVertexArray(sphere.mesh.VAO);
        glDrawArrays(GL_TRIANGLES, 0, sphere.mesh.vertexCount);

        glUseProgram(shaderProgram);
        setMat4Uniform(shaderProgram, "model", lightModel.mat);
        setMat4Uniform(shaderProgram, "view", view.mat);
        setMat4Uniform(shaderProgram, "projection", projection.mat);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, sphere.mesh.vertexCount);


        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glDeleteProgram(shaderProgram);
    glDeleteProgram(sphereProgram);
    glfwTerminate();

    return 0;
} 
