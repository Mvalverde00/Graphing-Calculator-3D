#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "opengl_all.h"
#include "mesh.h"

const size_t SAMPLES = 100;

/*
 * Represents a fixed rectangular prism of fixed width/length in the xy plane
 * and infinite extent in the z axis.  Used to render
 */
class Chunk {
  Mesh mesh;

  float startX, startY, endX, endY;

public:
  Chunk(float startX, float startY, float endX, float endY);
  void render();
  void reset();
  void rebuildMesh();

  Mesh& getMesh();
};

#endif
