#ifndef INCLUDED_DRILLER_SERVICES_TERRAIN_ALTERATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_TERRAIN_ALTERATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/ITerrainAlterationService.hpp>
#include <Driller/DataStructures/TerrainData.hpp>

namespace drl {
	
	class TerrainAlterationService : public ITerrainAlterationService {
	public:
		explicit TerrainAlterationService(TerrainData& _terrainData);
		~TerrainAlterationService(void) override;

		bool digShaft(int _level) override;
		bool digTile(int _level, int _x) override;
		void initialiseTile(int _level, int _column) override;

		bool doesTileExist(int _level, int _column) const override;
		bool doesLevelExist(int _level) const override;
		bool isTileDugOut(int _level, int _column) const override;

		void reserveJobOnTile(int _level, int _column) override;

		const TerrainTile& getTile(int _level, int _column) const override;

	private:
		TerrainData& m_TerrainData;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_TERRAIN_ALTERATION_SERVICE_HPP_