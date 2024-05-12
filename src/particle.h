#ifndef PARTICLE_H
#define PARTICLE_H

#include "linalg.h"

typedef struct {
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float radius;
} Particle;

void updateParticle(Particle *);
void handleCollision(Particle *, Particle *);

#endif // !PARTICLE_H
