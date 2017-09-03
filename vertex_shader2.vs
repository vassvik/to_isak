#version 450 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 instance_offset;
layout(location = 2) in vec2 instance_scale;

void main() {
    gl_Position = vec4(instance_offset + instance_scale*vertex_position, 0.0, 1.0);
}