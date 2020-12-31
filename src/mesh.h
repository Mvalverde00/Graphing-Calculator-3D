#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

#include "math/vectors.h"
#include "opengl_all.h"

class Mesh {
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  GLuint indicesSize;

public:
  Mesh(const std::vector<Vector3f>& vertices, const std::vector<int>& indices);
  Mesh();
  ~Mesh();

  Mesh& operator=(Mesh&& other);

  GLuint getIndicesSize();
  void bindVAO();
};

#endif
