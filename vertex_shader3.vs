#version 450 core

struct Quad {
	float ox, oy;
	float sx, sy;
};

layout (std430, binding = 0) buffer position_buffer {
    vec2 vertex_positions[];
};

layout (std430, binding = 1) buffer quad_buffer {
    Quad quads[];
};

void main() {
	// expand gl_VertexID to vertex positions
	vec2 p = vertex_positions[gl_VertexID];

	// use gl_InstanceID to grab offset and scale data
	Quad q = quads[gl_InstanceID];

	// transform
    gl_Position = vec4(vec2(q.ox, q.oy) + vec2(q.sx, q.sy)*p, 0.0, 1.0);
}

