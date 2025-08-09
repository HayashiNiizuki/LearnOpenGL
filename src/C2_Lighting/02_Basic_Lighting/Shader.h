#pragma once

#include <glad/glad.h>

#include <fstream>
#include <glm/matrix.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
 public:
  unsigned int ID;

  Shader(const char* vertexPath, const char* fragmentPath);
  void use();
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
  void setVec3(const std::string& name, float v1, float v2, float v3);
  void setMat4(const std::string& name, glm::mat4 mat);
};
