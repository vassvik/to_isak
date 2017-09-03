#version 330 core

uniform vec2 scale;
uniform vec2 offset;

layout(location = 0) in vec2 vertex_position;

void main() {
    gl_Position = vec4(offset + scale*vertex_position, 0.0, 1.0);
}