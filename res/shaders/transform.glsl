#version 330 core

layout(location = 0) in vec3 position;
// layout(location = 1) in vec2 texCoord;

// out vec2 vTexCoord;

uniform mat4 transform;

void main()
{
    vec4 pos = transform * vec4(position, 1.0);
    gl_Position = pos;
    // vTexcoord = texCoord;
}