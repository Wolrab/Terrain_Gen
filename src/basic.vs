#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vert_color; // TODO: Just get it inside the fragment shader?
out vec3 frag_color;

uniform mat4 PV;
uniform mat4 WM;

void main() {
    gl_Position = PV * WM * vec4(position, 1.0);
    frag_color = vert_color;
}