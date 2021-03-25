#include "chunk.h"

#include <iostream>
#include <vector>
#include <Engine/src/math/vectors.h>

float graphing_func(float x, float y) {
  //return 5*sin(x/2.0 + y/2.0);
  //return -1.0;
  return sin(x * 3.1415926) + sin(y * 3.1415926);
  //return x * x + y * y;
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

Chunk::Chunk(Vector3i chunkPos) :
    Chunk(chunkPos.x * CHUNK_SIZE, chunkPos.z * CHUNK_SIZE, chunkPos.x * CHUNK_SIZE + CHUNK_SIZE, chunkPos.z * CHUNK_SIZE + CHUNK_SIZE)
{};

Chunk::Chunk(ChunkData* data) {
  mesh = Engine::Mesh(data->vertices, data->indices);
}

Chunk::Chunk() {
    startX = endX = startY = endY = 0;
};

void Chunk::render() {}

void Chunk::reset() {
  mesh = Engine::Mesh({}, {});
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

  mesh = Engine::Mesh(vertices, indices);
}

Engine::Mesh& Chunk::getMesh() {
  return mesh;
}



Vector3i Chunk::getChunkPos(Vector3f pos) {
  // For now, the height component does not matter.  If I switch to marching cubes it will become
  // necessary as there will be vertical chunks.
  return Vector3i(floor(pos.x / CHUNK_SIZE), 0, floor(pos.z / CHUNK_SIZE));
}

ChunkData* Chunk::buildChunkData(Vector3i chunkPos) {
  ChunkData* data = new ChunkData();
  data->chunkPos = chunkPos;
  data->vertices = std::vector<Vector3f>();
  data->indices = std::vector<int>();

  float startX = chunkPos.x * CHUNK_SIZE;
  float endX = chunkPos.x * CHUNK_SIZE + CHUNK_SIZE;
  if (startX > endX) {
    float temp = startX;
    startX = endX;
    endX = temp;
  }
  float startY = chunkPos.z * CHUNK_SIZE;
  float endY = chunkPos.z * CHUNK_SIZE + CHUNK_SIZE;
  if (startY > endY) {
    float temp = startY;
    startY = endY;
    endY = temp;
  }

  float xStep = (endX - startX + 1) / SAMPLES;
  float yStep = (endY - startY + 1) / SAMPLES;
  std::cout << "xStep of " << xStep << " and yStep of " << yStep << "\n";

  // Create pool of vertices to draw from
  for (float xCount = 0; xCount < SAMPLES; xCount++) {
    for (float yCount = 0; yCount < SAMPLES; yCount++) {
      float x = startX + xCount * xStep;
      float y = startY + yCount * yStep;
      float z = graphing_func(x, y);
      Vector3f point = Vector3f(x, z, y);
      data->vertices.push_back(point);
    }
  }
  // Create indices for triangles using vertices
  for (int i = 0; i < SAMPLES - 1; i++) {
    for (int j = 0; j < SAMPLES - 1; j++) {
      int base = i + j * SAMPLES;
      // The top triangle
      data->indices.push_back(base);
      data->indices.push_back(base + 1);
      data->indices.push_back(base + 1 + SAMPLES);


      // The bottom triangle
      data->indices.push_back(base);
      data->indices.push_back(base + 1 + SAMPLES);
      data->indices.push_back(base + SAMPLES);
    }
  }

  return data;
}