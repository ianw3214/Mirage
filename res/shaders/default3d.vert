#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 vScreenCoord;
out vec2 vTexCoord;

// Model view projection matrix
uniform mat4 u_MVP;

void main() {
    vec4 pos = u_MVP * vec4(position, 1.0f);
	gl_Position = pos;
	vScreenCoord = vec3(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);
	vTexCoord = texCoord;	
}