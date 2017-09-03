#include "helpers.h" // declares window, resx and resy

int main() {
	int resx = 640, resy = 480;
	GLFWwindow *window = init(resx, resy); // initializes glfw, creates a window and loads opengl function pointers (via glad)
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	/*
	GLuint program = load_shaders("vertex_shader.vs", "fragment_shader.fs");
    if (program == 0) {
        fprintf(stderr, "Could not load shaders. Exiting\n");
        glfwTerminate();
        return -2;
    }
    */



    glClearColor(0.2, 0.3, 0.4, 1.0);
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
        calculate_frame_timings(window);

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}