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
	// expand gl_VertexID to vertex positions, assuming unit quads as the "primitive", matching glDrawArrays(GL_TRIANGLE_STRIP, 0, 4)
	int x = gl_VertexID / 2;
	int y = gl_VertexID % 2;
	vec2 p = vec2(x, y);

	// use gl_InstanceID to grab offset and scale data
	Quad q = quads[gl_InstanceID];

	// transform
    gl_Position = vec4(vec2(q.ox, q.oy) + vec2(q.sx, q.sy)*p, 0.0, 1.0);
}

