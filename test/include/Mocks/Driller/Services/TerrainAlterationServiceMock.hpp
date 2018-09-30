#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_TERRAIN_ALTERATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_TERRAIN_ALTERATION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/ITerrainAlterationService.hpp>

#include <functional>

namespace drl {
	
	class TerrainAlterationServiceMock : public ITerrainAlterationService {
	public:
		~TerrainAlterationServiceMock(void) override {}

		bool digShaft(int _level) override {
			if (digShaftCallback) {
				return digShaftCallback(_level);
			}
			return false;
		}

		bool digTile(int _level, int _x) override {
			if (digTileCallback) {
				return digTileCallback(_level, _x);
			}
			return false;
		}

		void initialiseTile(int _level, int _column) override {
			if (initialiseTileCallback) {
				initialiseTileCallback(_level, _column);
			}
		}

		bool doesTileExist(int _level, int _column) const override {
			if (doesTileExistCallback) {
				return doesTileExistCallback(_level, _column);
			}
			return false;
		}
		bool doesLevelExist(int _level) const override {
			if (doesLevelExistCallback) {
				return doesLevelExistCallback(_level);
			}
			return false;
		}
		bool isTileDugOut(int _level, int _column) const override {
			if (isTileDugOutCallback) {
				return isTileDugOutCallback(_level, _column);
			}
			return false;
		}

		void reserveJobOnTile(int _level, int _column) override {
			if (reserveJobOnTileCallback) {
				reserveJobOnTileCallback(_level, _column);
			}
		}

		const TerrainTile& getTile(int _level, int _column) const override {
			if (getTileCallback) {
				return getTileCallback(_level, _column);
			}

			return defaultTile;
		}

		TerrainTile defaultTile;

		std::function<bool(int)> digShaftCallback;
		std::function<bool(int, int)> digTileCallback;
		std::function<void(int, int)> initialiseTileCallback;
		std::function<bool(int, int)> doesTileExistCallback;
		std::function<bool(int)> doesLevelExistCallback;
		std::function<bool(int, int)> isTileDugOutCallback;
		std::function<void(int, int)> reserveJobOnTileCallback;
		std::function<const TerrainTile&(int, int)> getTileCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_TERRAIN_ALTERATION_SERVICE_MOCK_HPP_