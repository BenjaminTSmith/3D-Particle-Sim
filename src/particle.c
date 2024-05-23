#include "particle.h"

#define DAMPING_CONSTANT 0.7

void updateParticle(Particle *particle, float dt) {
    particle->velocity = vec3Add(particle->velocity, vec3ScalarMultiply(particle->acceleration, dt));
    particle->position = vec3Add(particle->position, vec3ScalarMultiply(particle->velocity, dt));
}

void checkContainerCollision(Particle *particle) {
    // SPHERE
    /*vec3 origin = {{ 0, 0, 0 }};
    float dist = vec3Distance(particle->position, origin) + particle->radius;
    if (dist >= 120) {
        vec3 direction = vec3Subtract(origin, particle->position);
        direction = normalizeVec3(direction);
        particle->position = vec3Add(particle->position, vec3ScalarMultiply(direction, dist - 120));
        direction = vec3Subtract(origin, particle->position);
        direction = normalizeVec3(direction);
        direction = vec3ScalarMultiply(direction, vec3Magnitude(particle->velocity) * DAMPING_CONSTANT);
        particle->velocity = direction;
    }*/
    // CUBE
    if (particle->position.x + particle->radius > 90) {
        particle->velocity.x = -particle->velocity.x * DAMPING_CONSTANT;
        particle->position.x = 90 - particle->radius;
    } if (particle->position.x - particle->radius < -90) {
        particle->velocity.x = -particle->velocity.x * DAMPING_CONSTANT;
        particle->position.x = -90 + particle->radius;
    } if (particle->position.z + particle->radius > 90) {
        particle->velocity.z = -particle->velocity.z * DAMPING_CONSTANT;
        particle->position.z = 90 - particle->radius;
    } if (particle->position.z - particle->radius < -90) {
        particle->velocity.z = -particle->velocity.z * DAMPING_CONSTANT;
        particle->position.z = -90 + particle->radius;
    } if (particle->position.y + particle->radius > 90) {
        particle->velocity.y = -particle->velocity.y * DAMPING_CONSTANT;
        particle->position.y = 90 - particle->radius;
    } if (particle->position.y - particle->radius < -90) {
        particle->velocity.y = -particle->velocity.y * DAMPING_CONSTANT;
        particle->position.y = -90 + particle->radius;
    }
}

void checkCollision(Particle *a, Particle *b) {
    float dist = vec3Distance(a->position, b->position);
    if (dist <= a->radius + b->radius) {
        vec3 normal = vec3Subtract(b->position, a->position);
        normal = normalizeVec3(normal);
        float change = a->radius + b->radius - dist;
        a->position = vec3Subtract(a->position, vec3ScalarMultiply(normal, 0.5 * change));
        b->position = vec3Add(b->position, vec3ScalarMultiply(normal, 0.5 * change));
        float aNormalScalar = vec3Multiply(a->velocity, normal);
        float bNormalScalar = vec3Multiply(b->velocity, normal);
        vec3 aNormal = vec3ScalarMultiply(normal, aNormalScalar * DAMPING_CONSTANT);
        vec3 bNormal = vec3ScalarMultiply(normal, bNormalScalar * DAMPING_CONSTANT);
        vec3 aTangent = vec3Subtract(a->velocity, aNormal);
        vec3 bTangent = vec3Subtract(b->velocity, bNormal);
        a->velocity = vec3Add(bNormal, aTangent);
        b->velocity = vec3Add(aNormal, bTangent);
    }
}
