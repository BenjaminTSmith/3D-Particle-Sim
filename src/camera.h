#ifndef CAMERA_H
#define CAMERA_H

#include "linalg.h"

typedef struct {
    float speed;
    vec3 position;
    vec3 front;
    vec3 up;
} Camera;

#endif // !CAMERA_H
