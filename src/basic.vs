#version 330

layout (location = 0) in vec4 Position;
out vec4 Color;
uniform float scale;

void main() {
    gl_Position = vec4(scale * Position.x, scale * Position.y, Position.z, Position.w);
    Color = vec4(clamp(Position, 0.0, 1.0));
}