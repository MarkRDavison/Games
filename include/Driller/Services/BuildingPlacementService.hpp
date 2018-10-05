#ifndef INCLUDED_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_HPP_

#include <Driller/DataStructures/BuildingData.hpp>
#include <Driller/Services/Interfaces/IBuildingPlacementService.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Driller/Services/Interfaces/IWorkerClassService.hpp>
#include <Driller/Services/Interfaces/ITerrainAlterationService.hpp>
#include "Interfaces/IShuttleDepartureService.hpp"

namespace drl {

	class BuildingPlacementService : public IBuildingPlacementService {
	public:
		BuildingPlacementService(BuildingData& _buildingData, ITerrainAlterationService& _terrainAlterationService, IBuildingPrototypeService& _buildingPrototypeService, IWorkerClassService& _workerClassService, IShuttleDepartureService& _shuttleDepartureService);
		~BuildingPlacementService(void) override;

		bool canPlacePrototype(const BuildingPrototypeId& _prototypeId, int _level, int _column) override;
		bool canPlacePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) override;
		void placePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) override;

	private:
		BuildingData& m_BuildingData;
		ITerrainAlterationService& m_TerrainAlterationService;
		IBuildingPrototypeService& m_BuildingPrototypeService;
		IWorkerClassService& m_WorkerClassService;
		IShuttleDepartureService& m_ShuttleDepartureService;
	};
	
}

#endif // INCLUDED_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_HPP_