#include "particle.h"

void updateParticle(Particle *particle) {
    particle->position = vec2Add(particle->position, particle->velocity);
    particle->velocity = vec2Add(particle->velocity, particle->acceleration);
    vec2 gravity = {{
        0, -0.5
    }};
    particle->acceleration = vec2Add(particle->acceleration, gravity);
}
