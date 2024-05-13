#include "linalg.h"

const mat4 identityMatrix = {{
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
}};

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

vec3 vec3Add(vec3 lhs, vec3 rhs) {
    vec3 result = {{
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
    }};
    return result;
}

float vec2Multiply(vec2 lhs, vec2 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float vec3Multiply(vec3 lhs, vec3 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

vec3 vec3ScalarMutliply(vec3 lhs, float scalar) {
    vec3 result = {{
        lhs.x * scalar,
        lhs.y * scalar,
        lhs.z * scalar,
    }};
    return result;
}

vec3 vec3Subtract(vec3 lhs, vec3 rhs) {
    vec3 result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

vec3 normalizeVec3(vec3 vec) {
    float magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    vec3 result = {{
        vec.x / magnitude,
        vec.y / magnitude,
        vec.z / magnitude,
    }};
    return result;
}

float vec4Multiply(vec4 lhs, vec4 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

vec3 crossVec3(vec3 lhs, vec3 rhs) {
    vec3 result = {{
        lhs.y * rhs.z - lhs.z * rhs.y,
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

mat4 mat4Multiply(mat4 lhs, mat4 rhs) {
    mat4 result = {{
        lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31 + lhs.m14 * rhs.m41,
        lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32 + lhs.m14 * rhs.m42,
        lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33 + lhs.m14 * rhs.m43,
        lhs.m11 * rhs.m14 + lhs.m12 * rhs.m24 + lhs.m13 * rhs.m34 + lhs.m14 * rhs.m44,

        lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31 + lhs.m24 * rhs.m41,
        lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32 + lhs.m24 * rhs.m42,
        lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33 + lhs.m24 * rhs.m43,
        lhs.m21 * rhs.m14 + lhs.m22 * rhs.m24 + lhs.m23 * rhs.m34 + lhs.m24 * rhs.m44,

        lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31 + lhs.m34 * rhs.m41,
        lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32 + lhs.m34 * rhs.m42,
        lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33 + lhs.m34 * rhs.m43,
        lhs.m31 * rhs.m14 + lhs.m32 * rhs.m24 + lhs.m33 * rhs.m34 + lhs.m34 * rhs.m44,

        lhs.m41 * rhs.m11 + lhs.m42 * rhs.m21 + lhs.m43 * rhs.m31 + lhs.m44 * rhs.m41,
        lhs.m41 * rhs.m12 + lhs.m42 * rhs.m22 + lhs.m43 * rhs.m32 + lhs.m44 * rhs.m42,
        lhs.m41 * rhs.m13 + lhs.m42 * rhs.m23 + lhs.m43 * rhs.m33 + lhs.m44 * rhs.m43,
        lhs.m41 * rhs.m14 + lhs.m42 * rhs.m24 + lhs.m43 * rhs.m34 + lhs.m44 * rhs.m44,
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
    vec3 direction = normalizeVec3(vec3Subtract(position, target));
    vec3 right = normalizeVec3(crossVec3(up, direction));
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

mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
    mat4 result = {{
        2 / (right - left), 0,                  0,                 - (right + left) / (right - left),
        0,                  2 / (top - bottom), 0,                 - (top + bottom / top - bottom),
        0,                  0,                  -2 / (far - near), - (far + near) / (far - near),
        0,                  0,                  0,                 1
    }};
    return result;
}

// FoV in radians
mat4 perspective(float fov, float aspectRatio, float front, float back) {
    float top = front * tan(fov / 2);
    float right = top * aspectRatio;
    mat4 result = {{
        front / right, 0,           0,                                 0,
        0,             front / top, 0,                                 0,
        0,             0,           - (back + front) / (back - front), - (2 * back * front) / (back - front),
        0,             0,           -1,                                0
    }};
    return result;
}
