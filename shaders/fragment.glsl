#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D container;

void main() {
    fragColor = texture(container, texCoord);
}
