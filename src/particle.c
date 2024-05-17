#include "particle.h"
#include "linalg.h"

void updateParticle(Particle *particle) {
    particle->position = vec3Add(particle->position, particle->velocity);
    particle->velocity = vec3Add(particle->velocity, particle->acceleration);
}

void checkCollision(Particle *a, Particle *b) {
    float dist = vec3Distance(a->position, b->position);
    if (dist <= a->radius + b->radius) {
    }
}
