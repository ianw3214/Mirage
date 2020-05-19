#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 transform;

void main()
{
    vec4 pos = vec4(position, 1.0) * transform;
    gl_Position = pos;
    vNormal = normal;
    vTexCoord = texCoord;
}