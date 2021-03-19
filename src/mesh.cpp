#include "mesh.h"

#include <iostream>

Mesh::Mesh(const std::vector<Vector3f>& vertices, const std::vector<int>& indices) : Mesh() {
  glGenVertexArrays(1, &vao);
  bindVAO();

  addVBO(vertices);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
  indicesSize = indices.size();
}

Mesh::Mesh(const std::vector<Vector3f>& vertices) : Mesh() {
  glGenVertexArrays(1, &vao);
  bindVAO();
  addVBO(vertices);
  indicesSize = vertices.size();
}

void Mesh::addVBO(const std::vector<Vector3f>& data) {
  bindVAO();

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  vbos.push_back(vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vector3f), &data[0], GL_STATIC_DRAW);

  glVertexAttribPointer(vbosSize, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), 0);
  glEnableVertexAttribArray(vbosSize);

  vbosSize++;
}

Mesh::Mesh() {
  vao = ebo = (GLuint) -1;
  vbosSize = 0;
}

Mesh::~Mesh() {
  if (vao != (GLuint)-1) {
    glDeleteVertexArrays(1, &vao);
    std::cout << "Deleted mesh data\n";
  }

  for (GLuint i = 0; i < vbosSize; i++) {
    glDeleteBuffers(1, &vbos[i]);
  }

  if (ebo != (GLuint)-1)
    glDeleteBuffers(1, &ebo);
}

Mesh& Mesh::operator=(Mesh&& other) {
  vao = other.vao;
  vbos = other.vbos;
  vbosSize = other.vbosSize;
  ebo = other.ebo;
  indicesSize = other.indicesSize;

  other.vao = other.ebo = (GLuint)-1;
  other.vbosSize = 0;
  return *this;
}

void Mesh::bindVAO() {
  if (vao != (GLuint)-1)
    glBindVertexArray(vao);
  else
    std::cout << "Attempted to bind uninitialized mesh!\n";
}

GLuint Mesh::getIndicesSize() {
  return indicesSize;
}
