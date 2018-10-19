#ifndef INCLUDED_SOVEREIGN_DATA_STRUCTURES_LEVEL_CHUNK_HPP_
#define INCLUDED_SOVEREIGN_DATA_STRUCTURES_LEVEL_CHUNK_HPP_

#include <Sovereign/DataStructures/LevelChunkCell.hpp>
#include <vector>

namespace sov {

	struct LevelChunk {
		int x;
		int y;
		std::vector<LevelChunkCell> cells;
	};

}

#endif // INCLUDED_SOVEREIGN_DATA_STRUCTURES_LEVEL_CHUNK_HPP_