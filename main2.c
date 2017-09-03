#include "helpers.h" // declares window, resx and resy

int main() {
	int resx = 640, resy = 480;
	GLFWwindow *window = init(resx, resy); // initializes glfw, creates a window and loads opengl function pointers (via glad)
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	
	GLuint program = load_shaders("vertex_shader2.vs", "fragment_shader.fs");
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

    GLuint vbo_position;
    glGenBuffers(1, &vbo_position);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
    
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), &vertex_data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(0, 0);


    float offset_data[] = {
        -0.4, -0.4,
         0.6,  0.5,
    };

    GLuint vbo_offset;
    glGenBuffers(1, &vbo_offset);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_offset);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(offset_data), &offset_data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(1, 1);


    float scale_data[] = {
        0.5, 0.5,
        0.3, 0.3,
    };

    GLuint vbo_scale;
    glGenBuffers(1, &vbo_scale);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_scale);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(scale_data), &scale_data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribDivisor(2, 1);

    
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
    glDeleteBuffers(1, &vbo_position);
    glDeleteBuffers(1, &vbo_offset);
    glDeleteBuffers(1, &vbo_scale);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}




