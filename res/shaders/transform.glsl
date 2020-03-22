#version 330 core

layout(location = 0) in vec3 position;
// layout(location = 1) in vec2 texCoord;

// out vec2 vTexCoord;
out vec3 debug_pos;

uniform mat4 transform;

void main()
{
    vec4 pos = vec4(position, 1.0) * transform;
    gl_Position = pos;
    // vTexcoord = texCoord;
    debug_pos = vec3(position);
}