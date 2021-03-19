#ifndef __CHUNK_MANGER_H__
#define __CHUNK_MANGER_H__

#include <unordered_map>
#include <vector>

#include "chunk.h"
#include "glm/gtx/hash.hpp"

const int RENDER_RADIUS = 3;
const int RENDER_RADIUS_SQD = RENDER_RADIUS * RENDER_RADIUS;

class ChunkManager {

	std::unordered_map<Vector3i, Chunk> loadedChunks;
	std::vector<Chunk*> visibleChunks;
	
	// Cache the previous position.  If we attempt to recenter on the same pos,
	// we can ignore the request.
	Vector3i prevChunkPos;

	//Generate chunk data in another thread

public:

	ChunkManager();

	void recenter(Vector3f pos);

	std::vector<Chunk*>& getVisibleChunks();

};

#endif