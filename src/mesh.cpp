#include "mesh.h"

#include <iostream>

Mesh::Mesh(const std::vector<Vector3f>& vertices, const std::vector<int>& indices) {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3f), &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
  indicesSize = indices.size();


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), 0);
  glEnableVertexAttribArray(0);

  std::cout << "created mesh buffers\n";
}

Mesh::Mesh() {
  vao = vbo = ebo = (GLuint) -1;
}

Mesh::~Mesh() {
  if (vao != (GLuint)-1) {
    glDeleteVertexArrays(1, &vao);
    std::cout << "Deleted mesh data\n";
  }

  if (vbo != (GLuint)-1)
    glDeleteBuffers(1, &vbo);

  if (ebo != (GLuint)-1)
    glDeleteBuffers(1, &ebo);
}

Mesh& Mesh::operator=(Mesh&& other) {
  vao = other.vao;
  vbo = other.vbo;
  ebo = other.ebo;
  indicesSize = other.indicesSize;

  other.vao = other.vbo = other.ebo = (GLuint)-1;
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

/*
void Mesh::render() {
  //glUseProgram
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}*/
