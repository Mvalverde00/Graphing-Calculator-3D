#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "opengl_all.h"
#include "mesh.h"

const int CHUNK_SIZE = 32;
const size_t SAMPLES = CHUNK_SIZE * 6;

/*
 * Represents a fixed rectangular prism of fixed width/length in the xy plane
 * and infinite extent in the z axis.  Used to render
 */
class Chunk {
  Mesh mesh;

  float startX, startY, endX, endY;

public:
  Chunk(float startX, float startY, float endX, float endY);
  Chunk(Vector3i chunkPos);
  Chunk();
  void render();
  void reset();
  void rebuildMesh();

  static Vector3i getChunkPos(Vector3f pos);

  Mesh& getMesh();
};

#endif
