#include "particle.h"
#include "linalg.h"

void updateParticle(Particle *particle, float dt) {
    particle->position = vec3Add(particle->position, vec3ScalarMultiply(particle->velocity, dt));
    particle->velocity = vec3Add(particle->velocity, vec3ScalarMultiply(particle->acceleration, dt));
}

void checkContainerCollision(Particle *particle) {
    //TODO: tweak this. if DAMPING_CONSTANT is too low, particles get stuck
    vec3 origin = {{ 0, 0, 0 }};
    float dist = vec3Distance(particle->position, origin) + particle->radius;
    if (dist >= 1.2) {
        vec3 direction = vec3Subtract(origin, particle->position);
        direction = normalizeVec3(direction);
        direction = vec3ScalarMultiply(direction, vec3Distance(particle->velocity, origin) * DAMPING_CONSTANT);
        particle->velocity = direction;
    }
}

void checkCollision(Particle *a, Particle *b) {
    float dist = vec3Distance(a->position, b->position);
    if (dist <= a->radius + b->radius) {
        vec3 origin = {{ 0, 0, 0 }};
        vec3 normal = vec3Subtract(b->position, a->position);
        normal = normalizeVec3(normal);
        float aMagnitude = vec3Distance(a->velocity, origin);
        float bMagnitude = vec3Distance(b->velocity, origin);
        b->velocity = vec3ScalarMultiply(vec3ScalarMultiply(normal, DAMPING_CONSTANT), aMagnitude);
        a->velocity = vec3ScalarMultiply(vec3ScalarMultiply(normal, -1 * DAMPING_CONSTANT), bMagnitude);
    }
}
