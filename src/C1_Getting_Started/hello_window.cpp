#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc, char *argv[]) {
    // 1.1 instantiate the GLFW window.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 1.2 create a window object. This window object holds all the windowing data and is required by most of GLFW's other functions.
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 1.3 initialize GLAD before we call any OpenGL function.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* 1.4 tell OpenGL the size of the rendering window
        The first two parameters of glViewport set the location of the lower left corner of the window.
        The third and fourth parameter set the width and height of the rendering window in pixels,
        which we set equal to GLFW's window size. */
    glViewport(0, 0, 800, 600);

    // However, the moment a user resizes the window the viewport should be adjusted as well.
    // We can register a callback function on the window that gets called each time the window is resized.

    // 1.5 tell GLFW we want to call this function on every window resize by registering it :
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 1.6 We want the application to keep drawing images and handling user input until the program has been explicitly told to stop.
    while (!glfwWindowShouldClose(window)) {
        // 1.8 check whether the user has pressed the escape key
        processInput(window);

        // 1.9 place all the rendering commands in the render loop

        // check and call events and swap the buffers
        glClearColor(0.4666666667f, 0.2f, 0.5529411765f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // 1.7 As soon as we exit the render loop we would like to properly clean/delete all of GLFW's resources that were allocated.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }
