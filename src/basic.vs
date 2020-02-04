#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vert_color; // TODO: Just get it inside the fragment shader?
out vec3 frag_color;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 world;
uniform mat4 model;

void main() {
    gl_Position = proj * view * world * model * vec4(position, 1.0);
    frag_color = vert_color;
}