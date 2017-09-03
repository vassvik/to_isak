#version 330 core

out vec4 color;

void main() {
	color = vec4(0.7, 0.4, 1.0, 1.0);
	if (gl_PrimitiveID == 0)
		color = vec4(1.0 - color.xyz, 1.0);
}