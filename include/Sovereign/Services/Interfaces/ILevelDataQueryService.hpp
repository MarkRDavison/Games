#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_QUERY_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_QUERY_SERVICE_HPP_

#include <Sovereign/DataStructures/LevelChunkCell.hpp>

namespace sov {

	class ILevelDataQueryService {
	protected:
		virtual ~ILevelDataQueryService(void) = 0;

	public:
		virtual bool doesLevelChunkExist(int _x, int _y) const = 0;
		
		virtual const LevelChunkCell& getLevelChunkCellForLevelChunk(int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) const = 0;
	};

	inline ILevelDataQueryService::~ILevelDataQueryService(void) = default;

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_QUERY_SERVICE_HPP_