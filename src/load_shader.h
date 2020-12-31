#ifndef __LOAD_SHADER_H__
#define __LOAD_SHADER_H__

#include <string>

#include "opengl_all.h"

GLuint load_shader(const std::string vertex_file, const std::string fragment_file);

#endif
