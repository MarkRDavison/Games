#include <Driller/Services/BuildingPlacementService.hpp>
#include <iostream>

namespace drl {

	BuildingPlacementService::BuildingPlacementService(BuildingData& _buildingData, ITerrainAlterationService& _terrainAlterationService, IBuildingPrototypeService& _buildingPrototypeService, IWorkerClassService& _workerClassService, IShuttleDepartureService& _shuttleDepartureService, inf::IResourceService& _resourceService) :
		m_BuildingData(_buildingData),
		m_TerrainAlterationService(_terrainAlterationService),
		m_BuildingPrototypeService(_buildingPrototypeService),
		m_WorkerClassService(_workerClassService),
		m_ShuttleDepartureService(_shuttleDepartureService),
		m_ResourceService(_resourceService) {
		
	}

	BuildingPlacementService::~BuildingPlacementService(void) {
		
	}

	bool BuildingPlacementService::canPlacePrototype(const GameCommand::CommandContext _context, const BuildingPrototypeId& _prototypeId, int _level, int _column) {
		GameCommand::PlaceBuildingEvent event{};
		event.prototypeId = _prototypeId;
		event.level = _level;
		event.column = _column;
		return canPlacePrototype(_context, event);
	}

	bool BuildingPlacementService::canPlacePrototype(const GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _placeBuilding) {
		if (!m_BuildingPrototypeService.isPrototypeRegistered(_placeBuilding.prototypeId)) {
			return false;
		}

		const BuildingPrototype& prototype = m_BuildingPrototypeService.getPrototype(_placeBuilding.prototypeId);

		if (_context == GameCommand::CommandContext::CreatingJob) {
			if (!m_ResourceService.canAfford(prototype.cost)) {
				return false;
			}
		}

		const int maxLevel = _placeBuilding.level + static_cast<int>(prototype.size.y);
		const int maxCol = _placeBuilding.column + static_cast<int>(prototype.size.x);

 		for (int level = _placeBuilding.level; level < maxLevel; ++level) {
			for (int col = _placeBuilding.column; col < maxCol; ++col) {
				if (!m_TerrainAlterationService.doesTileExist(level, col)) {
					return false;
				}
				const TerrainTile& tile = m_TerrainAlterationService.getTile(level, col);
				if (!tile.dugOut) {
					return false;
				}
				if (tile.jobReserved) {
					return false;
				}
				if (tile.hasBuilding) {
					return false;
				}
			}
		}

		return true;
	}

	const BuildingInstance& BuildingPlacementService::placePrototype(const GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _placeBuilding) {
		auto i = m_BuildingPrototypeService.createInstance(_placeBuilding.prototypeId);
		BuildingInstance& buildingInstance = m_BuildingData.buildings.emplace_back(i);
		buildingInstance.coordinates = { _placeBuilding.column, _placeBuilding.level };

		if (buildingInstance.providedWorkerPrototypeId != 0u) {
			m_WorkerClassService.increaseClassMaximum(buildingInstance.providedWorkerPrototypeId, buildingInstance.providedWorkerPrototypeAmount);
			m_ShuttleDepartureService.addWorkerPrototypeToQueue(buildingInstance.providedWorkerPrototypeId);
		}

		const int maxLevel = _placeBuilding.level + static_cast<int>(buildingInstance.size.y);
		const int maxCol = _placeBuilding.column + static_cast<int>(buildingInstance.size.x);

		for (int level = _placeBuilding.level; level < maxLevel; ++level) {
			for (int col = _placeBuilding.column; col < maxCol; ++col) {
				m_TerrainAlterationService.placeBuildingOnTile(level, col, true);
			}
		}

		return buildingInstance;
	}

}
