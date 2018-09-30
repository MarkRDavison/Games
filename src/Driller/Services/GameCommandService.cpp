#include <Driller/Services/GameCommandService.hpp>

namespace drl {

	GameCommandService::GameCommandService(inf::IResourceService& _resourceService, ITerrainAlterationService& _terrainAlterationService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, IJobCreationService& _jobCreationService, IJobPrototypeService& _jobPrototypeService, IJobAllocationService& _jobAllocationService, IWorkerPrototypeService& _workerPrototypeService) :
		GameCommandService(_resourceService, _terrainAlterationService, _buildingPlacementService, _buildingPrototypeService, _jobCreationService, _jobPrototypeService, _jobAllocationService, _workerPrototypeService, 0ll) {
		
	}
	GameCommandService::GameCommandService(inf::IResourceService& _resourceService, ITerrainAlterationService& _terrainAlterationService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, IJobCreationService& _jobCreationService, IJobPrototypeService& _jobPrototypeService, IJobAllocationService& _jobAllocationService, IWorkerPrototypeService& _workerPrototypeService, long long _startTick) :
		m_ResourceService(_resourceService),
		m_TerrainAlterationService(_terrainAlterationService),
		m_BuildingPlacementService(_buildingPlacementService),
		m_BuildingPrototypeService(_buildingPrototypeService),
		m_JobCreationService(_jobCreationService),
		m_JobPrototypeService(_jobPrototypeService),
		m_JobAllocationService(_jobAllocationService),
		m_WorkerPrototypeService(_workerPrototypeService),
		m_CurrentTick(_startTick) {
		
	}
	GameCommandService::~GameCommandService(void) {
		
	}

	void GameCommandService::tick(void) {
		m_CurrentTick++;
	}
	long long GameCommandService::getCurrentTick(void) const {
		return m_CurrentTick;
	}

	bool GameCommandService::executeGameCommand(const GameCommand& _command) {
		switch (_command.type) {
		case GameCommand::PlaceBuilding:
			return handlePlaceBuildingCommand(_command.placeBuilding);
		case GameCommand::DigTile:
			return handleDigTileCommand(_command.digTile);
		case GameCommand::DigShaft:
			return handleDigShaftCommand(_command.digShaft);
		case GameCommand::AdjustResouce: 
			return handleAdjustResourceCommand(_command.adjustResource);
		case GameCommand::CreateJob:
			return handleCreateJobCommand(_command.createJob);
		case GameCommand::ResetJobAllocations:
			return handleResetJobAllocationsCommand(_command.resetJobAllocations);
		default:
			return false;
		}
	}

	bool GameCommandService::handlePlaceBuildingCommand(const GameCommand::PlaceBuildingEvent& _event) const {
		if (!m_BuildingPlacementService.canPlacePrototype(_event)) {
			return false;
		}

		m_BuildingPlacementService.placePrototype(_event);

		return true;
	}

	bool GameCommandService::handleDigShaftCommand(const GameCommand::DigShaftEvent& _event) const {
		return m_TerrainAlterationService.digShaft(_event.level);
	}

	bool GameCommandService::handleDigTileCommand(const GameCommand::DigTileEvent& _event) const {
		return m_TerrainAlterationService.digTile(_event.level, _event.column);
	}

	bool GameCommandService::handleAdjustResourceCommand(const GameCommand::AdjustResourceEvent& _event) const {
		if (!m_ResourceService.canAfford(_event.resourceId, _event.amount)) {
			return false;
		}

		m_ResourceService.payResourceId(_event.resourceId, _event.amount);
		
		return true;
	}

	bool GameCommandService::handleCreateJobCommand(const GameCommand::CreateJobEvent& _event) const {
		if (!m_JobCreationService.canCreateJob(_event)) {
			return false;
		}

		m_JobCreationService.createJob(_event);

		return true;
	}

	bool GameCommandService::handleResetJobAllocationsCommand(const GameCommand::ResetJobAllocationsEvent& _event) const {
		m_JobAllocationService.resetJobAllocations();
		return true;
	}
}
