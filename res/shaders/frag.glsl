#version 330 core

out vec4 colour;
in vec3 debug_pos;

uniform vec4 u_Colour;

void main() {
    // colour = u_Colour;
    float r = (debug_pos.x + 1.0) / 2.0;
    float g = (debug_pos.y + 1.0) / 2.0;
    float b = (debug_pos.z + 1.0) / 2.0;
    colour = vec4(r, g, b, 1.0);
}