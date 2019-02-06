#version 400 core

in vec3 vPos;
in vec3 vNormal;
out vec4 colour;

uniform vec3 lightColour;
uniform vec3 objectColour;
uniform vec3 lightPos;

void main() {
    // Ambient lighting
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColour;

    // Diffuse lighting
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;

    // Calculate the result
    vec3 result = (ambient + diffuse) * objectColour;
    colour = vec4(result, 1.0);
}