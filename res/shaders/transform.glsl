#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 vRawPos;
out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 pos = vec4(position, 1.0) * model * view * projection;
    gl_Position = pos;

    // outputs
    vRawPos = vec3(vec4(position, 1.0) * model);
    vNormal = normal;
    vTexCoord = texCoord;
}