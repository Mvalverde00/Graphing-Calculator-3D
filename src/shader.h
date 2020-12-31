#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

#include "opengl_all.h"
#include "math/vectors.h"

class Shader {
  GLuint id;

public:
  Shader(std::string vertex_file, std::string fragment_file);
  Shader();
  ~Shader();

  void set_float(std::string name, float val);
  void set_int(std::string name, int val);
  void set_matrix4f(std::string name, Matrix4f matrix);
  void use();
};

#endif
