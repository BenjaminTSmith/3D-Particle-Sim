#version 330 core

in vec3 normal;
in vec3 FragPos;

out vec4 FragColor;
  
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = diff * lightColor;

    FragColor = vec4((ambient + diffuse) * objectColor, 1);
}
