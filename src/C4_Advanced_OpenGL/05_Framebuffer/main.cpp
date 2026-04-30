#include <cstddef>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"
#include "preprocessor.h"
#include "utils.h"

void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void mouse_button_callback(GLFWwindow*, int, int, int);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool leftMousePressed = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // tell GLFW to capture our mouse
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  // clang-format off
  float floorVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f
  };

  float rightVerticles[] = {
     0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
  };
  
  float leftVerticles[] = {
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  };

  float lightVerticles[] = {
    -0.25f, 0.49999f, -0.25f,  0.0f, -1.0f,  0.0f,
     0.25f, 0.49999f, -0.25f,  0.0f, -1.0f,  0.0f,
     0.25f, 0.49999f,  0.25f,  0.0f, -1.0f,  0.0f,
     0.25f, 0.49999f,  0.25f,  0.0f, -1.0f,  0.0f,
    -0.25f, 0.49999f,  0.25f,  0.0f, -1.0f,  0.0f,
    -0.25f, 0.49999f, -0.25f,  0.0f, -1.0f,  0.0f,
  };

  float *vertexBufferData[] = {floorVertices, leftVerticles, rightVerticles};
  unsigned int vertexSize[] = {sizeof(floorVertices), sizeof(leftVerticles), sizeof(rightVerticles)};
  // clang-format on

  unsigned int planeVAOs[3], planeVBOs[3];
  glGenVertexArrays(3, planeVAOs);
  glGenBuffers(3, planeVBOs);

  for (int i = 0; i < 3; i++) {
    glBindVertexArray(planeVAOs[i]);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBOs[i]);
    glBufferData(GL_ARRAY_BUFFER, vertexSize[i], vertexBufferData[i], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }

  unsigned int lightVAO, lightVBO;
  glGenVertexArrays(1, &lightVAO);
  glGenBuffers(1, &lightVBO);

  glBindVertexArray(lightVAO);
  glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(lightVerticles), lightVerticles, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  Shader triShader((exec_dir() / "shaders" / "normalTri" / "shader.vs").string().c_str(), (exec_dir() / "shaders" / "normalTri" / "shader.fs").string().c_str());
  Shader lightShader((exec_dir() / "shaders" / "light" / "shader.vs").string().c_str(), (exec_dir() / "shaders" / "light" / "shader.fs").string().c_str());

  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    triShader.use();
    triShader.setMat4("model", model);
    triShader.setMat4("view", view);
    triShader.setMat4("projection", projection);
    triShader.setVec3("lightPos", 0.f, 0.49999f, 0.f);
    triShader.setVec3("lightColor", 1.f, 1.0f, 1.f);
    triShader.setVec3("viewPos", camera.Position);

    glBindVertexArray(planeVAOs[0]);
    triShader.setVec3("objColor", 192. / 255., 167. / 255., 139. / 255.);
    glDrawArrays(GL_TRIANGLES, 0, 18);

    glBindVertexArray(planeVAOs[1]);
    triShader.setVec3("objColor", 1., 0., 0.);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(planeVAOs[2]);
    triShader.setVec3("objColor", 0., 1., 0.);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    lightShader.use();
    lightShader.setMat4("model", model);
    lightShader.setMat4("view", view);
    lightShader.setMat4("projection", projection);

    glBindVertexArray(lightVAO);
    lightShader.setVec3("objColor", 1., 1., 1.);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  float currentFrame = glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  const float cameraSpeed = 2.5f * deltaTime;  // adjust accordingly
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
  else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
  else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
  else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
  else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
  else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  if (leftMousePressed) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
  } else {
    lastX = xpos;
    lastY = ypos;
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      // 鼠标左键被按下
      leftMousePressed = true;
    } else if (action == GLFW_RELEASE) {
      // 鼠标左键被释放
      leftMousePressed = false;
    }
  }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}
