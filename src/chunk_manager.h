#ifndef __CHUNK_MANGER_H__
#define __CHUNK_MANGER_H__

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "chunk.h"
#include "glm/gtx/hash.hpp"
#include "threading/threadsafe_queue.h"

const int RENDER_RADIUS = 3;
const int RENDER_RADIUS_SQD = RENDER_RADIUS * RENDER_RADIUS;

class ChunkManager {

	std::unordered_map<Vector3i, Chunk> loadedChunks;
	std::vector<Chunk*> visibleChunks;

	// The main thread will populate this vector with chunks it wants loaded.
	// An auxilary thread will then grab the chunks, process their loading,
	// and push them the other vector.  The main thread will then retrieve this
	// data and use it to create a chunk, at a far lesser cost.
	ThreadsafeQueue<Vector3i> chunksToLoad;
	ThreadsafeQueue<ChunkData*> chunksAwaitingFinish;
	std::unordered_set<Vector3i> chunksBeingLoaded;
	std::thread chunkLoader;

	void startLoadingChunk(Vector3i chunkPos);
	void loadChunkLoop(); // Function called by thread.
	
	// Cache the previous position.  If we attempt to recenter on the same pos,
	// we can ignore the request.
	Vector3i prevChunkPos;


public:

	ChunkManager();

	void update();
	void recenter(Vector3f pos);

	std::vector<Chunk*>& getVisibleChunks();

};

#endif