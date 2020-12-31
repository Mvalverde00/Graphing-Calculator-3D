#include "shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "opengl_all.h"
#include "load_shader.h"

Shader::Shader(std::string vertex_file, std::string fragment_file) {
  this->id = load_shader(vertex_file, fragment_file);
}

Shader::Shader() {
  this->id = -1;
}

Shader::~Shader() {
  glDeleteShader(id);
}

void Shader::set_float(std::string name, float val) {
  GLuint location = glGetUniformLocation(id, name.c_str());
  glUniform1f(location, val);
}

void Shader::set_int(std::string name, int val) {
  GLuint location = glGetUniformLocation(id, name.c_str());
  glUniform1i(location, val);
}

void Shader::set_matrix4f(std::string name, Matrix4f matrix) {
  GLuint location = glGetUniformLocation(id, name.c_str());
  if (location == (GLuint)-1) {
    std::cout << name << " is not a uniform in the shader\n";
  }
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::use() {
  if (id != (GLuint)-1) {
    glUseProgram(id);
  }
}
