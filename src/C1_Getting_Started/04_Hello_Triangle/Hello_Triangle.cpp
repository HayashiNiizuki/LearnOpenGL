#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSourceNogi = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(0.4666666667f, 0.2f, 0.5529411765f, 1.0f);\n"
                                       "}\n\0";
const char *fragmentShaderSourceKeya = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(0.4588235294f, 0.7176470588f, 0.3607843137f, 1.0f);\n"
                                       "}\n\0";

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // vertexs and indices
    float vertexes[] = {
        -0.4f, +0.8f, 0.0f, // A 0
        -0.0f, +0.8f, 0.0f, // B 1
        +0.4f, +0.8f, 0.0f, // C 2
        -0.8f, +0.0f, 0.0f, // D 3
        -0.4f, +0.0f, 0.0f, // E 4
        +0.4f, +0.0f, 0.0f, // F 5
        +0.8f, +0.0f, 0.0f, // G 6
        -0.4f, -0.8f, 0.0f, // H 7
        -0.0f, -0.8f, 0.0f, // I 8
        +0.4f, -0.8f, 0.0f, // J 9
    };

    unsigned int vertices[4][6] = {{0, 1, 4, 4, 3, 0}, {1, 2, 6, 6, 5, 1}, {3, 4, 8, 8, 7, 3}, {5, 6, 9, 9, 8, 5}};

    // compile all shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderNogi = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderKeya = glCreateShader(GL_FRAGMENT_SHADER);
    // unsigned int fragmentShaderKeya = glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int shaderProgramNogi = glCreateProgram();
    unsigned int shaderProgramKeya = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShaderNogi, 1, &fragmentShaderSourceNogi, NULL);
    glCompileShader(fragmentShaderNogi);
    glShaderSource(fragmentShaderKeya, 1, &fragmentShaderSourceKeya, NULL);
    glCompileShader(fragmentShaderKeya);

    glAttachShader(shaderProgramNogi, vertexShader);
    glAttachShader(shaderProgramNogi, fragmentShaderNogi);
    glLinkProgram(shaderProgramNogi);

    glAttachShader(shaderProgramKeya, vertexShader);
    glAttachShader(shaderProgramKeya, fragmentShaderKeya);
    glLinkProgram(shaderProgramKeya);

    unsigned int VBO;
    unsigned int EBOs[4];
    unsigned int VAOs[4];
    glGenBuffers(1, &VBO);
    glGenBuffers(4, EBOs);
    glGenVertexArrays(4, VAOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    for (int i = 0; i < 4; i++) {
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // Vertex attributes stay the same
        glEnableVertexAttribArray(0);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderNogi);
    glDeleteShader(fragmentShaderKeya);

    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramNogi);
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[3]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgramKeya);
        glBindVertexArray(VAOs[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // for (int i = 0; i < 4; i++) {
        //     glBindVertexArray(VAOs[i]);
        //     // glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, 0);
        //     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // }
        glBindVertexArray(0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}