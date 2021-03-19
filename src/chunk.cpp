#include "chunk.h"

#include <iostream>
#include <vector>

#include "math/vectors.h"

float graphing_func(float x, float y) {
    return 5*sin(x/2.0 + y/2.0);
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
  this->endX += 1;
  this->endY += 1;
  rebuildMesh();
}

Chunk::Chunk(Vector3i chunkPos) :
    Chunk(chunkPos.x * CHUNK_SIZE, chunkPos.z * CHUNK_SIZE, chunkPos.x * CHUNK_SIZE + CHUNK_SIZE - 1, chunkPos.z * CHUNK_SIZE + CHUNK_SIZE - 1)
{};

Chunk::Chunk() {
    startX = endX = startY = endY = 0;
};

Vector3i Chunk::getChunkPos(Vector3f pos) {
  // For now, the height component does not matter.  If I switch to marching cubes it will become
  // necessary as there will be vertical chunks.
  return Vector3i((int)pos.x / CHUNK_SIZE, 0, (int)pos.z / CHUNK_SIZE);
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
      Vector3f point = Vector3f(x, z, y);
      vertices.push_back(point);
    }
  }

  // Create indices for triangles using vertices
  for (int i = 0; i < SAMPLES - 1; i++) {
    for (int j = 0; j < SAMPLES - 1; j++) {
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

  mesh = Mesh(vertices, indices);
}

Mesh& Chunk::getMesh() {
  return mesh;
}
