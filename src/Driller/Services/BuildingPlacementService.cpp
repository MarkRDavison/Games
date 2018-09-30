#include <Driller/Services/BuildingPlacementService.hpp>

namespace drl {

	BuildingPlacementService::BuildingPlacementService(BuildingData& _buildingData, const TerrainData& _terrainData, IBuildingPrototypeService& _buildingPrototypeService) :
		m_BuildingData(_buildingData),
		m_TerrainData(_terrainData),
		m_BuildingPrototypeService(_buildingPrototypeService) {
		
	}

	BuildingPlacementService::~BuildingPlacementService(void) {
		
	}

	bool BuildingPlacementService::canPlacePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) {
		if (!m_BuildingPrototypeService.isPrototypeRegistered(_placeBuilding.prototypeId)) {
			return false;
		}

		const BuildingPrototype& prototype = m_BuildingPrototypeService.getPrototype(_placeBuilding.prototypeId);

		const int maxLevel = _placeBuilding.level + static_cast<int>(prototype.size.y);
		const int maxCol = _placeBuilding.column + static_cast<int>(prototype.size.x);

		for (int level = _placeBuilding.level; level < maxLevel; ++level) {
			for (int col = _placeBuilding.column; col < maxCol; ++col) {
				if (!m_TerrainData.tileExists(level, col)) {
					return false;
				}
				const TerrainTile& tile = m_TerrainData.getTile(level, col);
				if (!tile.dugOut) {
					return false;
				}
			}
		}

		return true;
	}

	void BuildingPlacementService::placePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) {
		BuildingInstance& buildingInstance = m_BuildingData.buildings.emplace_back(m_BuildingPrototypeService.createInstance(_placeBuilding.prototypeId));
		buildingInstance.coordinates = { _placeBuilding.column, _placeBuilding.level };
	}

}
