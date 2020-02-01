#version 330

layout (location = 0) in vec3 Position;

uniform float scale;

void main() {
    gl_Position = vec4(scale * Position.x, scale * Position.y, Position.z, 1.0);
}