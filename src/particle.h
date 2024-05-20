#ifndef PARTICLE_H
#define PARTICLE_H

#define DAMPING_CONSTANT 0.5

#include "linalg.h"

typedef struct {
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    float radius;
} Particle;

void updateParticle(Particle *, float);
void checkContainerCollision(Particle *);
void checkCollision(Particle *, Particle *);

#endif // !PARTICLE_H
