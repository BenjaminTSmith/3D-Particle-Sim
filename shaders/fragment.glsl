#version 330 core
out vec4 fragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D container;

void main() {
    fragColor = texture(container, texCoord) * vec4(vec3(1, 0, 0), 1);
}
