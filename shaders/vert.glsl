#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 model;
out vec3 v_color;

void main() {
    v_color = color;
    vec4 position = vec4(pos, 1.0);
    gl_Position = model * position;
}
