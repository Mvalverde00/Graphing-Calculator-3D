#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <Engine/src/opengl_all.h>
#include <Engine/src/mesh.h>

const int CHUNK_SIZE = 32;
const size_t SAMPLES = CHUNK_SIZE * 6;


/*
 * Everything needed to construct a chunk, with the
 * heavy lifting computation already performed.
 */
struct ChunkData {
  Vector3i chunkPos;
  std::vector<Vector3f> vertices;
  std::vector<int> indices;
};


/*
 * Represents a fixed rectangular prism of fixed width/length in the xy plane
 * and infinite extent in the z axis.  Used to render
 */
class Chunk {
  Engine::Mesh mesh;
  Vector3i pos;
  float startX, startY, endX, endY;

public:
  Chunk(float startX, float startY, float endX, float endY);
  Chunk(Vector3i chunkPos);
  Chunk(ChunkData* data);
  Chunk();
  void render();
  void reset();
  void rebuildMesh();

  Engine::Mesh& getMesh();



  static Vector3i getChunkPos(Vector3f pos);
  static ChunkData* buildChunkData(Vector3i chunkPos);
};

#endif
