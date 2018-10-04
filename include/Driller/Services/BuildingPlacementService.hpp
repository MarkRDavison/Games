#ifndef INCLUDED_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_HPP_

#include <Driller/DataStructures/BuildingData.hpp>
#include <Driller/Services/Interfaces/IBuildingPlacementService.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Driller/DataStructures/TerrainData.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>
#include "Interfaces/IWorkerClassService.hpp"

namespace drl {

	class BuildingPlacementService : public IBuildingPlacementService {
	public:
		BuildingPlacementService(BuildingData& _buildingData, const TerrainData& _terrainData, IBuildingPrototypeService& _buildingPrototypeService, IWorkerClassService& _workerClassService);
		~BuildingPlacementService(void) override;

		bool canPlacePrototype(const BuildingPrototypeId& _prototypeId, int _level, int _column) override;
		bool canPlacePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) override;
		void placePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) override;

	private:
		BuildingData& m_BuildingData;
		const TerrainData& m_TerrainData;
		IBuildingPrototypeService& m_BuildingPrototypeService;
		IWorkerClassService& m_WorkerClassService;
	};
	
}

#endif // INCLUDED_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_HPP_