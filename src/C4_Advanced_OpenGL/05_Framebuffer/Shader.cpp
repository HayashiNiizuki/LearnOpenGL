#include "Shader.h"

#include <fstream>
#include <glm/fwd.hpp>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

Shader::Shader(std::string vertexSdFile, std::string fragmentSdFile) {
  unsigned int fs, vs;
  std::ifstream vsFile, fsFile;
  std::string vsString, fsString;

  vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // open and read file safely
  try {
    vsFile.open(vertexSdFile);
    fsFile.open(fragmentSdFile);

    std::ostringstream vsStream, fsStream;
    vsStream << vsFile.rdbuf();
    fsStream << fsFile.rdbuf();

    vsString = vsStream.str();
    fsString = fsStream.str();
  } catch (const std::ifstream::failure& e) {
    std::cout << "SHADER FILE READ ERROR" << std::endl;
  }

  // create shader
  vs = glCreateShader(GL_VERTEX_SHADER);
  fs = glCreateShader(GL_FRAGMENT_SHADER);

  const char* vsContent = vsString.c_str();
  const char* fsContent = fsString.c_str();

  glShaderSource(vs, 1, &vsContent, NULL);
  glShaderSource(fs, 1, &fsContent, NULL);

  glad_glCompileShader(vs);
  glad_glCompileShader(fs);

  // check shader compile result
  int success;
  char infoLog[512];
  // vertex shader
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // fragment shader
  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fs, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // create shader program
  id = glCreateProgram();
  glad_glAttachShader(id, vs);
  glad_glAttachShader(id, fs);
  glLinkProgram(id);

  glDeleteShader(vs);
  glDeleteShader(fs);
}

void Shader::use() {
  glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float v1, float v2, float v3) {
  glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

void Shader::setVec3(const std::string& name, glm::vec3 v3) {
  glUniform3f(glGetUniformLocation(id, name.c_str()), v3.x, v3.y, v3.z);
}

void Shader::setMat4(const std::string& name, glm::mat4 mat) {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}