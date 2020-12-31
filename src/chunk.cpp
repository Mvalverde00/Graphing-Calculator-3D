#include "chunk.h"

#include <vector>
#include "math/vectors.h"
#include <iostream>

float graphing_func(float x, float y) {
  return sin(y) + x;
}

Chunk::Chunk(float startX, float startY, float endX, float endY) {
  if (startX > endX) {
    this->startX = endX;
    this->endX = startX;
  } else {
    this->startX = startX;
    this->endX = endX;
  }

  if (startY > endY) {
    this->startY = endY;
    this->endY = startY;
  } else {
    this->startY = startY;
    this->endY = endY;
  }
  rebuildMesh();
}

void Chunk::render() {

}

void Chunk::reset() {
  mesh = Mesh({}, {});
}

void Chunk::rebuildMesh() {
  std::vector<Vector3f> vertices;
  std::vector<int> indices;

  float xStep = (endX - startX + 1)/SAMPLES;
  float yStep = (endY - startY + 1)/SAMPLES;

  // Create pool of vertices to draw from
  for (float xCount = 0; xCount < SAMPLES; xCount++) {
    for (float yCount = 0; yCount < SAMPLES; yCount++) {
      float x = startX + xCount*xStep;
      float y = startY + yCount*yStep;
      float z = graphing_func(x, y);
      Vector3f point = Vector3f(x, y, z);
      vertices.push_back(point);
    }
  }

  // Create indices for triangles using vertices
  for (int i = 0; i < SAMPLES; i++) {
    for (int j = 0; j < 4; j++) {
      int base = i + j*SAMPLES;
      // The top triangle
      indices.push_back(base);
      indices.push_back(base + 1);
      indices.push_back(base + 1 + SAMPLES);


      // The bottom triangle
      indices.push_back(base);
      indices.push_back(base + 1 + SAMPLES);
      indices.push_back(base + SAMPLES);
    }
  }

  /*vertices = {
     Vector3f(0.5f,  0.5f, 0.5f),  // top right
     Vector3f(0.5f, -0.5f, 0.5f),  // bottom right
    Vector3f(-0.5f, -0.5f, 0.5f),  // bottom left
    Vector3f(-0.5f,  0.5f, 0.5f),  // top left
  };

  indices = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };*/

  mesh = Mesh(vertices, indices);
  std::cout << "There are " << vertices.size() << "samples and " << indices.size() << "\n";
}

Mesh& Chunk::getMesh() {
  return mesh;
}
