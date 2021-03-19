#ifndef __MESH_H__
#define __MESH_H__

#include <vector>

#include "math/vectors.h"
#include "opengl_all.h"

class Mesh {
  GLuint vao;
  std::vector<GLuint> vbos;
  GLuint vbosSize;
  GLuint ebo;

  // Length of ebo, if one is provided.  Otherwise it is the length of the vertices VBO.
  GLuint indicesSize;

public:
  Mesh(const std::vector<Vector3f>& vertices, const std::vector<int>& indices);
  Mesh(const std::vector<Vector3f>& vertices);
  Mesh();
  ~Mesh();

  Mesh& operator=(Mesh&& other);

  GLuint getIndicesSize();
  void bindVAO();
  void addVBO(const std::vector<Vector3f>& data);
};

#endif
