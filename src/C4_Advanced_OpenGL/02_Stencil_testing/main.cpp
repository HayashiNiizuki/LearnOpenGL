#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "preprocessor.h"
#include "utils.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void mouse_button_callback(GLFWwindow*, int, int, int);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool leftMousePressed = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(0.6f, 0.4f, 1.0f);

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

  // clang-format off
  float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
  };
  // positions all containers
  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };
  // positions of the point lights
  glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
  };
  // clang-format on

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // 初始化 ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  ImFont* my_font = io.Fonts->AddFontFromFileTTF((exec_dir() / "resources" / "NotoSansSC-Medium.otf").c_str(), 30.0f);
  io.FontDefault = my_font;

  // 设置样式
  ImGui::StyleColorsDark();

  // 初始化平台/渲染器后端
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_STENCIL_TEST);

  glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  // lightVAO
  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  // we only need to bind to the VBO, the container's VBO's data already
  // contains the data.
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // set the vertex attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // cubeVAO
  unsigned int cubeVAO;
  glGenVertexArrays(1, &cubeVAO);
  glBindVertexArray(cubeVAO);
  // we only need to bind to the VBO, the container's VBO's data already
  // contains the data.
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // set the vertex attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // 法线属性
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // 纹理坐标属性
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  Shader cubeShader((exec_dir() / "shaders" / "cube_shader" / "shader.vs").string().c_str(), (exec_dir() / "shaders" / "cube_shader" / "shader.fs").string().c_str());
  Shader lightShader((exec_dir() / "shaders" / "lighting_shader" / "shader.vs").string().c_str(), (exec_dir() / "shaders" / "lighting_shader" / "shader.fs").string().c_str());
  Shader shaderSingleColor((exec_dir() / "shaders" / "single_color_shader" / "shader.vs").string().c_str(), (exec_dir() / "shaders" / "single_color_shader" / "shader.fs").string().c_str());

  unsigned int diffuseMap = loadTexture((exec_dir() / "resources" / "container2.png").string().c_str());
  unsigned int specularMap = loadTexture((exec_dir() / "resources" / "container2_specular.png").string().c_str());
  cubeShader.use();
  cubeShader.setInt("material.diffuse", 0);
  cubeShader.setInt("material.specular", 1);

  char location_x[12], location_y[12], location_z[12];
  char viewport_x[12], viewport_y[12], viewport_z[12];

  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    // --------------------

    // input
    // -----
    processInput(window);

    glClearColor(0.05f, 0.05f, 0.05f, 0.05f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);  // also clear the depth buffer now!

    cubeShader.use();
    // object material
    cubeShader.setVec3("viewPos", camera.Position);
    cubeShader.setFloat("material.shininess", 64.0f);
    // light properties
    cubeShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    cubeShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    cubeShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    cubeShader.setVec3("pointLights[0].position", pointLightPositions[0]);
    cubeShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[0].constant", 1.0f);
    cubeShader.setFloat("pointLights[0].linear", 0.09f);
    cubeShader.setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    cubeShader.setVec3("pointLights[1].position", pointLightPositions[1]);
    cubeShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[1].constant", 1.0f);
    cubeShader.setFloat("pointLights[1].linear", 0.09f);
    cubeShader.setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    cubeShader.setVec3("pointLights[2].position", pointLightPositions[2]);
    cubeShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[2].constant", 1.0f);
    cubeShader.setFloat("pointLights[2].linear", 0.09f);
    cubeShader.setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    cubeShader.setVec3("pointLights[3].position", pointLightPositions[3]);
    cubeShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[3].constant", 1.0f);
    cubeShader.setFloat("pointLights[3].linear", 0.09f);
    cubeShader.setFloat("pointLights[3].quadratic", 0.032f);
    // spotLight
    cubeShader.setVec3("spotLight.position", camera.Position);
    cubeShader.setVec3("spotLight.direction", camera.Front);
    cubeShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    cubeShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    cubeShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("spotLight.constant", 1.0f);
    cubeShader.setFloat("spotLight.linear", 0.09f);
    cubeShader.setFloat("spotLight.quadratic", 0.032f);
    cubeShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    cubeShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    cubeShader.setMat4("projection", projection);
    cubeShader.setMat4("view", view);

    // world transformation
    // glm::mat4 model = glm::mat4(1.0f);
    // cubeShader.setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    glBindVertexArray(cubeVAO);
    for (unsigned int i = 0; i < 10; i++) {
      // calculate the model matrix for each object and pass it to shader before
      // drawing
      glStencilFunc(GL_ALWAYS, 1, 0xFF);
      glStencilMask(0xFF);

      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      cubeShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    glBindVertexArray(cubeVAO);

    shaderSingleColor.use();
    for (unsigned int i = 0; i < 10; i++) {
      // calculate the model matrix for each object and pass it to shader before
      // drawing
      glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
      glStencilMask(0x00);

      float scale = 1.05f;

      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      model = glm::scale(model, glm::vec3(scale, scale, scale));
      shaderSingleColor.setMat4("projection", projection);
      shaderSingleColor.setMat4("view", view);
      shaderSingleColor.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);

    lightShader.use();
    lightShader.setVec3("lightColor", 0.95f, 0.95f, 0.95f);
    lightShader.setMat4("projection", projection);
    lightShader.setMat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.1f));  // a smaller cube
    lightShader.setMat4("model", model);

    glBindVertexArray(lightVAO);
    for (unsigned int i = 0; i < 4; i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, pointLightPositions[i]);
      model = glm::scale(model, glm::vec3(0.2f));  // Make it a smaller cube
      lightShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("CAMERA");
    ImGui::Text("Camera Location");

    std::snprintf(location_x, sizeof(location_x), "%.4f", camera.Position.x);
    std::snprintf(location_y, sizeof(location_y), "%.4f", camera.Position.y);
    std::snprintf(location_z, sizeof(location_z), "%.4f", camera.Position.z);

    ImGui::Text("x");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputText("##x", location_x, IM_COUNTOF(location_x), ImGuiInputTextFlags_ReadOnly);

    ImGui::SameLine();
    ImGui::Text("y");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputText("##y", location_y, IM_COUNTOF(location_y), ImGuiInputTextFlags_ReadOnly);

    ImGui::SameLine();
    ImGui::Text("z");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputText("##z", location_z, IM_COUNTOF(location_z), ImGuiInputTextFlags_ReadOnly);

    ImGui::Text("Camera Viewport");

    std::snprintf(viewport_x, sizeof(viewport_x), "%.4f", camera.Front.x);
    std::snprintf(viewport_y, sizeof(viewport_y), "%.4f", camera.Front.y);
    std::snprintf(viewport_z, sizeof(viewport_z), "%.4f", camera.Front.z);

    ImGui::Text("x");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputText("##x", viewport_x, IM_COUNTOF(viewport_x), ImGuiInputTextFlags_ReadOnly);

    ImGui::SameLine();
    ImGui::Text("y");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputText("##y", viewport_y, IM_COUNTOF(viewport_y), ImGuiInputTextFlags_ReadOnly);

    ImGui::SameLine();
    ImGui::Text("z");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputText("##z", viewport_z, IM_COUNTOF(viewport_z), ImGuiInputTextFlags_ReadOnly);

    ImGui::End();

    // 渲染
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
  ImGuiIO& io = ImGui::GetIO();
  if (io.WantCaptureMouse) {
    return;
  }

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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}