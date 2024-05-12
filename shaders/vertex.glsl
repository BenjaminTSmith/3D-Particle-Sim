#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 iColor;
layout (location = 2) in vec2 iTexCoord;

out vec3 color;
out vec2 texCoord;

void main() {
    gl_Position = vec4(vec2(pos.x, pos.y), 0, 1);
    color = iColor;
    texCoord = iTexCoord;
}
