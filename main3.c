#include "helpers.h" // declares window, resx and resy

int main() {
	int resx = 640, resy = 480;
	GLFWwindow *window = init(resx, resy); // initializes glfw, creates a window and loads opengl function pointers (via glad)
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	
	GLuint program = load_shaders("vertex_shader3.vs", "fragment_shader.fs");
    if (program == 0) {
        fprintf(stderr, "Could not load shaders. Exiting\n");
        glfwTerminate();
        return -2;
    }
    
        // setup vao
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    float vertex_data[] = {
        -1.0, -1.0,
         1.0, -1.0,
        -1.0,  1.0,
         1.0,  1.0,
    };

    float quads[] = {
        -0.4, -0.4,   0.5, 0.5,
         0.6,  0.5,   0.3, 0.3,
    };

    GLuint buf_positions, buf_quads;
    glCreateBuffers(1, &buf_positions);
    glCreateBuffers(1, &buf_quads);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buf_positions);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buf_quads);

    glNamedBufferData(buf_positions, sizeof(vertex_data), &vertex_data[0], GL_STATIC_DRAW);
    glNamedBufferData(buf_quads,     sizeof(quads),       &quads[0],       GL_STATIC_DRAW);


    glClearColor(0.2, 0.3, 0.4, 1.0);
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
        calculate_frame_timings(window);

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);

        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 2);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(program);
    glDeleteBuffers(1, &buf_positions);
    glDeleteBuffers(1, &buf_quads);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}




