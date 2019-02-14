#version 400 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;
out vec4 colour;

uniform vec3 objectColour;

uniform vec3 sunColour;
uniform vec3 sunDir;

void main() {
    float ambientStrength = 0.5;

    // Sun shit
    vec3 sun_ambient = ambientStrength * sunColour;
    vec3 sun_diffuse = max(dot(normalize(vNormal), -1.f * sunDir), 0.0) * sunColour;

    // Calculate the result
    colour = vec4(sun_ambient + sun_diffuse, 1.0) * vec4(objectColour, 1.f);
    // colour = vec4(vNormal, 1.f);
}