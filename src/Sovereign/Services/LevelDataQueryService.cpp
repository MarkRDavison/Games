#include <Sovereign/Services/LevelDataQueryService.hpp>
#include <Sovereign/Core/Definitions.hpp>
#include <algorithm>
#include <cassert>

namespace sov {

	LevelDataQueryService::LevelDataQueryService(const LevelData& _levelData) :
		m_LevelData(_levelData) {
		
	}
	LevelDataQueryService::~LevelDataQueryService(void) {
		
	}

	bool LevelDataQueryService::doesLevelChunkExist(int _x, int _y) const {
		const auto result = std::find_if(m_LevelData.levelChunks.begin(), m_LevelData.levelChunks.end(), [_x, _y](const LevelChunk& _level) -> bool { return _level.x == _x && _level.y == _y; });
		return result != m_LevelData.levelChunks.end();
	}
	const LevelChunkCell& LevelDataQueryService::getLevelChunkCellForLevelChunk(int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) const {
		assert(doesLevelChunkExist(_chunkX, _chunkY));

		const LevelChunk& chunk = *std::find_if(m_LevelData.levelChunks.begin(), m_LevelData.levelChunks.end(), [_chunkX, _chunkY](const LevelChunk& _level) -> bool { return _level.x == _chunkX && _level.y == _chunkY; });

		return chunk.cells[(_cellY % Definitions::ChunkSize) * Definitions::ChunkSize + (_cellX % Definitions::ChunkSize)];
	}

}
