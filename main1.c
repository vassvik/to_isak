#include "helpers.h" // declares window, resx and resy

int main() {
	int resx = 640, resy = 480;
	GLFWwindow *window = init(resx, resy); // initializes glfw, creates a window and loads opengl function pointers (via glad)
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	
	GLuint program = load_shaders("vertex_shader1.vs", "fragment_shader.fs");
    if (program == 0) {
        fprintf(stderr, "Could not load shaders. Exiting\n");
        glfwTerminate();
        return -2;
    }
    
        // setup vao
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // setup vbo
    float vertex_data[] = {
        -1.0, -1.0,
         1.0, -1.0,
        -1.0,  1.0,
         1.0,  1.0,
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), &vertex_data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glClearColor(0.2, 0.3, 0.4, 1.0);
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
        calculate_frame_timings(window);

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);

        glUniform2f(glGetUniformLocation(program, "scale"), 0.5, 0.5);
        glUniform2f(glGetUniformLocation(program, "offset"), -0.4, -0.4);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glUniform2f(glGetUniformLocation(program, "scale"), 0.3, 0.3);
        glUniform2f(glGetUniformLocation(program, "offset"), 0.6, 0.5);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}




