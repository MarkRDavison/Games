#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_QUERY_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_QUERY_SERVICE_MOCK_HPP_

#include <Sovereign/Services/Interfaces/ILevelDataQueryService.hpp>
#include <Utility/TestSignal.hpp>

namespace sov {

	class LevelDataQueryServiceMock : public ILevelDataQueryService {
	public:
		~LevelDataQueryServiceMock(void) override {}

		bool doesLevelChunkExist(int _x, int _y) const override {
			return doesLevelChunkExistCallback.invoke(_x, _y);
		}
		const LevelChunkCell& getLevelChunkCellForLevelChunk(int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) const override {
			return getLevelChunkCellForLevelChunkCallback.invoke(_chunkX, _chunkY, _cellX, _cellY);
		}

		inf::TestSignal<bool, int, int> doesLevelChunkExistCallback;
		inf::TestSignal<const LevelChunkCell&, int, int, unsigned, unsigned> getLevelChunkCellForLevelChunkCallback;
	};

}

#endif // INCLUDED_MOCKS_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_QUERY_SERVICE_MOCK_HPP_