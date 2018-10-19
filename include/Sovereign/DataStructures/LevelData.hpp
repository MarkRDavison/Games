#ifndef INCLUDED_SOVEREIGN_DATA_STRUCTURES_LEVEL_DATA_HPP_
#define INCLUDED_SOVEREIGN_DATA_STRUCTURES_LEVEL_DATA_HPP_

#include <Sovereign/DataStructures/LevelChunk.hpp>
#include <vector>

namespace sov {
	
	struct LevelData {
		std::vector<LevelChunk> levelChunks;
	};

}

#endif // INCLUDED_SOVEREIGN_DATA_STRUCTURES_LEVEL_DATA_HPP_