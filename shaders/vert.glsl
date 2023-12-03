#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 mvp;
out vec3 v_color;

void main() {
    v_color = color;
    gl_Position = mvp * vec4(pos, 1.);
}
