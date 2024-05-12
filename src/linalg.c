#include "linalg.h"

vec2 vec2Add(vec2 lhs, vec2 rhs) {
    vec2 result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    return result;
}

vec2 vec2Subtract(vec2 lhs, vec2 rhs) {
    vec2 result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    return result;
}

float vec2Multiply(vec2 lhs, vec2 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float vec3Multiply(vec3 lhs, vec3 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float vec4Multiply(vec4 lhs, vec4 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

vec3 crossVec3(vec3 lhs, vec3 rhs) {
    vec3 result = {{
        lhs.y * rhs.z - lhs.x * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    }};
    return result;
}

vec2 mat2Vec2Multiply(mat2 lhs, vec2 rhs) {
    vec2 result = {{
        lhs.m11 * rhs.x + lhs.m12 * rhs.y,
        lhs.m21 * rhs.x + lhs.m22 * rhs.y
    }};
    return result;
}

mat2 mat2Multiply(mat2 lhs, mat2 rhs) {
    mat2 result = {{
        lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21, lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22,
        lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21, lhs.m21 * rhs.m12 + lhs.m21 * rhs.m22
    }};
    return result;
}

vec2 rotateVec2(vec2 vec, float theta) {
    mat2 transform = {{
        cos(theta), -sin(theta),
        sin(theta), cos(theta)
    }};   
    return mat2Vec2Multiply(transform, vec);
}

mat4 lookAt(vec3 position, vec3 target, vec3 up) {
    vec3 direction = vec3Subtract(target, position);
    vec3 right = crossVec3(up, direction);
    mat4 coordinateSpace = {{
        right.x,     right.y,     right.z,     0,
        up.x,        up.y,        up.z,        0,
        direction.x, direction.y, direction.z, 0,
        0,           0,           0,           1
    }};

    mat4 camera = {{
        1, 0, 0, -position.x,
        0, 1, 0, -position.y,
        0, 0, 1, -position.z,
        0, 0, 0, 1
    }};

    return mat4Multiply(coordinateSpace, camera);
}
