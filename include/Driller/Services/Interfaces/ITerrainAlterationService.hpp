#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_TERRAIN_ALTERATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_TERRAIN_ALTERATION_SERVICE_HPP_

#include <Driller/DataStructures/TerrainTile.hpp>

namespace drl {
	
	class ITerrainAlterationService {
	public:
		virtual ~ITerrainAlterationService(void) = 0 {}

		virtual bool digShaft(int _level) = 0;
		virtual bool digTile(int _level, int _x) = 0;
		virtual void initialiseTile(int _level, int _column) = 0;

		virtual bool doesTileExist(int _level, int _column) const = 0;
		virtual bool doesLevelExist(int _level) const = 0;
		virtual bool isTileDugOut(int _level, int _column) const = 0;

		virtual void reserveJobOnTile(int _level, int _column, bool _jobReserved) = 0;
		virtual void placeBuildingOnTile(int _level, int _column, bool _placeBuilding) = 0;

		virtual const TerrainTile& getTile(int _level, int _column) const = 0;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_TERRAIN_ALTERATION_SERVICE_HPP_