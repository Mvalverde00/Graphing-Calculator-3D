#include "chunk_manager.h"

#include <iostream>

ChunkManager::ChunkManager() {
	// Set cached pos to some non-zero pos, so that we can
	// recenter it to 0,0,0 and generate the relevant chunks
	prevChunkPos = Vector3i(1, 0, 0);
	recenter(Vector3f(0, 0, 0));
	chunkLoader = std::thread(&ChunkManager::loadChunkLoop, this);
};

void ChunkManager::update() {

	// since we are the only consumer, this should be safe
	while (!chunksAwaitingFinish.unsafeEmpty()) {
		ChunkData* data = chunksAwaitingFinish.dequeue();

		//TODO: add chunk to map and remove from set
		loadedChunks[data->chunkPos] = Chunk(data);
		chunksBeingLoaded.erase(data->chunkPos);

		delete data;

		recenter(prevChunkPos);
	}
}

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
			bool alreadyGenerated = loadedChunks.find(currChunkPos) != loadedChunks.end();
			bool beingLoaded = chunksBeingLoaded.find(currChunkPos) != chunksBeingLoaded.end();
			if (!alreadyGenerated && !beingLoaded ) {
				//loadedChunks[currChunkPos] = Chunk(currChunkPos);
				startLoadingChunk(currChunkPos);
			}
			else if (alreadyGenerated) {
				visibleChunks.push_back(&loadedChunks[currChunkPos]);
			}
		}
	}

	std::cout << "recentering!!\n";
}

void ChunkManager::startLoadingChunk(Vector3i chunkPos) {
	chunksBeingLoaded.insert(chunkPos);
	chunksToLoad.enqueue(chunkPos);
}

void ChunkManager::loadChunkLoop() {
	while (true) {
		Vector3i chunkToLoad = chunksToLoad.dequeue();
		std::cout << "Begining load of chunk at " << chunkToLoad.x << ", " << chunkToLoad.z << "\n";
		ChunkData* data = Chunk::buildChunkData(chunkToLoad);
		chunksAwaitingFinish.enqueue(data);
	}
}

std::vector<Chunk*>& ChunkManager::getVisibleChunks() {
	return visibleChunks;
}