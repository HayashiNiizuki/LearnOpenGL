#pragma once

#include <string>

#include <glm/glm.hpp>

class Shader {
 public:
  Shader(std::string vertexSdFile, std::string fragmentSdFile);

  void use();

  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
  void setVec3(const std::string& name, float v1, float v2, float v3);
  void setMat4(const std::string& name, glm::mat4 mat);

 private:
  unsigned int id;
};