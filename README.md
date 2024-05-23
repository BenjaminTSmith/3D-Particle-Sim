# 3D Particle Simulator
This project was HEAVILY inspired by Gradience's video:
https://www.youtube.com/watch?v=NorXFOobehY&t=228s

## Implicit Euler Method

The particles are updated using the implicit Euler method, which means that
the position vector is updated with the next frames velocity vector rather than
the current frames. This tends to lead to more stable results:
```
v(t + dt) = v(t) + a(t) * dt
x(t + dt) = x(t) + v(t + dt) * dt
```
Collision detection is a very simple, naive solution, where the distance
between the particles is checked against the radii of the particles added
together. If the distance is too short, the velocity vectors are projected onto
the normal vector, and the particles positions are shifted apart.

## Dependencies

This project requires glfw3 and GLEW. If you are on Ubuntu, apt-install these
packages and the Makefile should work on your machine.
