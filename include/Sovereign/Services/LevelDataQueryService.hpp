#ifndef INCLUDED_SOVEREIGN_SERVICES_LEVEL_DATA_QUERY_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_LEVEL_DATA_QUERY_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/ILevelDataQueryService.hpp>
#include <Sovereign/DataStructures/LevelData.hpp>

namespace sov {
	
	class LevelDataQueryService : public ILevelDataQueryService {
	public:
		LevelDataQueryService(const LevelData& _levelData);
		~LevelDataQueryService(void) override;

		bool doesLevelChunkExist(int _x, int _y) const override;
		const LevelChunkCell& getLevelChunkCellForLevelChunk(int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) const override;


	private:
		const LevelData& m_LevelData;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_LEVEL_DATA_QUERY_SERVICE_HPP_