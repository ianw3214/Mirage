#version 330 core

out vec4 colour;

in vec3 vRawPos;
in vec3 vNormal;
in vec2 vTexCoord;

uniform vec4 u_Colour;
uniform vec3 u_Camera;

// Constants
// TODO: Make adjustable
const vec3 lightColor = vec3(1.0, 1.0, 0.8);
const vec3 lightDir = vec3(0.0, 1.0, 0.0);

void main() {
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(vNormal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * 0.7;

    float specularStrength = 0.1;
    vec3 viewDir = normalize(u_Camera - vRawPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(u_Colour);
    colour = vec4(result, 1.0);
}