#ifndef LINALG_H
#define LINALG_H

#include <math.h>

#define PI 3.1415926535897932384626433832795

typedef union {
    struct {
        float x, y;
    };
    float vec[2];
} vec2;

typedef union {
    struct {
        float x, y, z;
    };
    float vec[3];
} vec3;

typedef union {
    struct {
        float x, y, z, w;
    };
    float vec[4];
} vec4;

typedef union {
    struct {
        float m11, m12,
              m21, m22;
    };
    float mat[4];
} mat2;

typedef union {
    struct {
        float m11, m12, m13,
              m21, m22, m23,
              m31, m32, m33;
    };
    float mat[9];
} mat3;

typedef union {
    struct {
        float m11, m12, m13, m14,
              m21, m22, m23, m24,
              m31, m32, m33, m34,
              m41, m42, m43, m44;
    };
    float mat[16];
} mat4;

extern const mat4 identityMatrix;

float degToRadians(float);

vec2 vec2Add(vec2, vec2);
vec2 vec2Subtract(vec2, vec2);
vec3 vec3Add(vec3, vec3);
vec3 vec3Subtract(vec3, vec3);

vec3 normalizeVec3(vec3);

float vec2Multiply(vec2, vec2);
float vec3Multiply(vec3, vec3);
float vec4Multiply(vec4, vec4);

vec3 vec3ScalarMultiply(vec3, float);

float vec3Distance(vec3, vec3);

vec3 crossVec3(vec3, vec3);

vec2 mat2Vec2Multiply(mat2, vec2);
vec3 mat3Vec3Multiply(mat3, vec3);
vec4 mat4Vec4Multiply(mat4, vec4);

mat2 mat2Multiply(mat2, mat2);
mat3 mat3Multiply(mat3, mat3);
mat4 mat4Multiply(mat4, mat4);

vec2 rotateVec2(vec2, float theta);

mat4 scale(mat4, vec3);
mat4 translate(mat4, vec3);

mat4 lookAt(vec3, vec3, vec3);

mat4 ortho(float, float, float, float, float, float);
mat4 perspective(float, float, float, float);

#endif // !LINALG_H
