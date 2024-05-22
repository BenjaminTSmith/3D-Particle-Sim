#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "linalg.h"
#include "camera.h"
#include "shader.h"
#include "mesh.h"
#include "particle.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define PARTICLE_COUNT 200

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

    ShaderID containerProgram = createShader("shaders/sphere_vertex.glsl", "shaders/sphere_fragment.glsl");
    ShaderID particleProgram = createShader("shaders/particle_vertex.glsl", "shaders/particle_fragment.glsl");

    Mesh sphereMesh = createMesh("models/sphere.obj");
    Mesh cubeMesh = createMesh("models/cube.obj");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.12, 0.1, 0.11, 1.0);

    float cameraRadius = 500;
    Camera camera;
    vec3 position = {{ 0, 0.3, cameraRadius }};
    vec3 front = {{ 0, 0, -1 }};
    vec3 up = {{ 0, 1, 0 }};
    camera.position = position;
    camera.front = front;
    camera.up = up;
    camera.speed = 0.05;

    float dt = 0;
    float lastFrame = 0;

    vec3 origin = {{ 0, 0, 0 }};
    mat4 projection = perspective(PI / 4, 16. / 9., 0.1, 1000);

    Particle particles[PARTICLE_COUNT];
    vec3 gravity = {{ 0, -200, 0 }};
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].radius = 5;
        vec3 position = {{ i / 2., i / 3., i / 4. }};
        particles[i].position = position;
        vec3 velocity = {{ sin(i) * 100, sin(rand() % 2) * 100, cos(rand() % 2) * 100 }};
        particles[i].velocity = velocity;
        particles[i].acceleration = gravity;
    }

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        float frame = glfwGetTime();
        dt = frame - lastFrame;
        lastFrame = frame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            for (int i = 0; i < PARTICLE_COUNT; i++) {
                vec3 attraction = vec3Subtract(origin, particles[i].position);
                attraction = normalizeVec3(attraction);
                particles[i].acceleration = vec3ScalarMultiply(attraction, 500);
            }
        } 
        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
            for (int i = 0; i < PARTICLE_COUNT; i++) {
                particles[i].acceleration = gravity;
            }
        } 
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            for (int i = 0; i < PARTICLE_COUNT; i++) {
                particles[i].acceleration = origin;
            }
        }

        camera.position.x = sin(glfwGetTime() / 3) * cameraRadius;
        camera.position.z = cos(glfwGetTime() / 3) * cameraRadius;
        camera.front = normalizeVec3(vec3Subtract(origin, camera.position));
        mat4 view = lookAt(camera.position, vec3Add(camera.front, camera.position), camera.up);

        glUseProgram(containerProgram);
        vec3 sphereScale = {{ 120, 120, 120 }};
        mat4 model = scale(identityMatrix, sphereScale);
        setMat4Uniform(containerProgram, "model", model.mat);
        setMat4Uniform(containerProgram, "view", view.mat);
        setMat4Uniform(containerProgram, "projection", projection.mat);

        glBindVertexArray(sphereMesh.VAO);
        glDrawArrays(GL_POINTS, 0, sphereMesh.vertexCount);

        glUseProgram(particleProgram);
        vec3 lightPos = {{ 100, 200, 0 }};
        vec3 lightColor = {{ 1, 1, 1 }};
        vec3 objectColor = {{ 1, 0, 0 }};
        setVec3Uniform(particleProgram, "lightPos", lightPos.vec);
        setVec3Uniform(particleProgram, "lightColor", lightColor.vec);
        setVec3Uniform(particleProgram, "objectColor", objectColor.vec);
        setMat4Uniform(particleProgram, "view", view.mat);
        setMat4Uniform(particleProgram, "projection", projection.mat);
        for (int i= 0; i < PARTICLE_COUNT; i++) {
            vec3 particleScale = {{ 
                particles[i].radius,
                particles[i].radius,
                particles[i].radius
            }};
            mat4 model = scale(identityMatrix, particleScale);
            model = translate(model, particles[i].position);
            setMat4Uniform(particleProgram, "model", model.mat);
            glDrawArrays(GL_TRIANGLES, 0, sphereMesh.vertexCount);
        }

        for (int i = 0; i < PARTICLE_COUNT; i++) {
            for (int j = i + 1; j < PARTICLE_COUNT; j++) {
                checkCollision(&particles[i], &particles[j]);
            }
            checkContainerCollision(&particles[i]);
            updateParticle(&particles[i], dt);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glDeleteProgram(containerProgram);
    glfwTerminate();

    return 0;
} 
