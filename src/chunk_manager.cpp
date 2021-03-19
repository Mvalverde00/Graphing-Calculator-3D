#include "chunk_manager.h"

#include <iostream>

ChunkManager::ChunkManager() {};

void ChunkManager::recenter(Vector3f pos) {
	Vector3i chunkPos = Chunk::getChunkPos(pos);

	if (chunkPos == prevChunkPos) {
	  return;
	}
	prevChunkPos = chunkPos;

	visibleChunks.clear();

	// Iterator over chunks in circle about center
	for (int x = -RENDER_RADIUS; x < RENDER_RADIUS; x++) {
		int hh = (int)std::sqrt(RENDER_RADIUS_SQD - x * x);
		int rx = chunkPos.x + x;
		int ph = chunkPos.z + hh;

		for (int z = chunkPos.z - hh; z < ph; z++) {
			Vector3i currChunkPos = Vector3f(rx, 0, z);
			
			// If the key is not present, generate it and add it.  Otherwise, just add it.
			// TODO: move chunk generation to another thread
			if (loadedChunks.find(currChunkPos) == loadedChunks.end()) {
				loadedChunks[currChunkPos] = Chunk(currChunkPos);
			}
			visibleChunks.push_back(&loadedChunks[currChunkPos]);
		}
	}

	std::cout << "recentering!!\n";
}

std::vector<Chunk*>& ChunkManager::getVisibleChunks() {
	return visibleChunks;
}