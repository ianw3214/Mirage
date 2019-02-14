#version 400 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;
out vec4 colour;

uniform vec3 sunColour;
uniform vec3 sunDir;

uniform sampler2D u_Texture;

void main() {
    float ambientStrength = 0.5;

    /*
    // Ambient lighting
    vec3 ambient = ambientStrength * lightColour;

    // Diffuse lighting
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;
    */

    // Sun shit
    vec3 sun_ambient = ambientStrength * sunColour;
    vec3 sun_diffuse = max(dot(normalize(vNormal), -1.f * sunDir), 0.0) * sunColour;

    // Calculate the result
    vec4 textureColour = texture(u_Texture, vTexCoord);
    // colour = vec4(sun_ambient + sun_diffuse, 1.0) * vec4(ambient + diffuse, 1.0) * textureColour;
    colour = vec4(sun_ambient + sun_diffuse, 1.0) * textureColour;
}