#version 400 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;
out vec4 colour;

uniform vec3 lightColour;
uniform vec3 objectColour;
uniform vec3 lightPos;

uniform sampler2D u_Texture;

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
    vec4 textureColour = texture(u_Texture, vTexCoord);
    colour = vec4(ambient + diffuse, 1.0) * textureColour;
}