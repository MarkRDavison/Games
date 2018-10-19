#include <Driller/Services/GameCommandService.hpp>
#include <iostream>

namespace drl {

	GameCommandService::GameCommandService(inf::IResourceService& _resourceService, ITerrainAlterationService& _terrainAlterationService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, IJobCreationService& _jobCreationService, IJobPrototypeService& _jobPrototypeService, IJobAllocationService& _jobAllocationService, IWorkerCreationService& _workerCreationService, IWorkerPrototypeService& _workerPrototypeService, IShuttleCreationService& _shuttleCreationService, ICostService& _costService) :
		GameCommandService(_resourceService, _terrainAlterationService, _buildingPlacementService, _buildingPrototypeService, _jobCreationService, _jobPrototypeService, _jobAllocationService, _workerCreationService, _workerPrototypeService, _shuttleCreationService, _costService, 0ll) {
		
	}
	GameCommandService::GameCommandService(inf::IResourceService& _resourceService, ITerrainAlterationService& _terrainAlterationService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, IJobCreationService& _jobCreationService, IJobPrototypeService& _jobPrototypeService, IJobAllocationService& _jobAllocationService, IWorkerCreationService& _workerCreationService, IWorkerPrototypeService& _workerPrototypeService, IShuttleCreationService& _shuttleCreationService, ICostService& _costService, long long _startTick) :
		m_ResourceService(_resourceService),
		m_TerrainAlterationService(_terrainAlterationService),
		m_BuildingPlacementService(_buildingPlacementService),
		m_BuildingPrototypeService(_buildingPrototypeService),
		m_JobCreationService(_jobCreationService),
		m_JobPrototypeService(_jobPrototypeService),
		m_JobAllocationService(_jobAllocationService),
		m_WorkerCreationService(_workerCreationService),
		m_WorkerPrototypeService(_workerPrototypeService),
		m_ShuttleCreationService(_shuttleCreationService),
		m_CostService(_costService),	
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
			return handlePlaceBuildingCommand(_command.commandContext, _command.placeBuilding);
		case GameCommand::DigTile:
			return handleDigTileCommand(_command.commandContext, _command.digTile);
		case GameCommand::DigShaft:
			return handleDigShaftCommand(_command.commandContext, _command.digShaft);
		case GameCommand::AdjustResouce: 
			return handleAdjustResourceCommand(_command.commandContext, _command.adjustResource);
		case GameCommand::CreateJob:
			return handleCreateJobCommand(_command.commandContext, _command.createJob);
		case GameCommand::ResetJobAllocations:
			return handleResetJobAllocationsCommand(_command.commandContext, _command.resetJobAllocations);
		case GameCommand::CreateWorker:
			return handleCreateWorkerCommand(_command.commandContext, _command.createWorker);
		case GameCommand::CreateShuttle:
			return handleCreateShuttleCommand(_command.commandContext, _command.createShuttle);
		default:
			return false;
		}
	}

	bool GameCommandService::handlePlaceBuildingCommand(const GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _event) const {
		if (!m_BuildingPlacementService.canPlacePrototype(_context, _event)) {
			return false;
		}

		const BuildingInstance& instance = m_BuildingPlacementService.placePrototype(_context, _event);

		const BuildingPrototype& prototype = m_BuildingPrototypeService.getPrototype(_event.prototypeId);

		if (prototype.providesJobs) {
			m_JobCreationService.createJobsForPlacedBuilding(prototype, instance);
		}

		return true;
	}

	bool GameCommandService::handleDigShaftCommand(const GameCommand::CommandContext _context, const GameCommand::DigShaftEvent& _event) const {
		if (_context != GameCommand::CommandContext::Undefined) {
			const int digShaftCost = m_CostService.getDigShaftCost(_event.level);
			GameCommand::AdjustResourceEvent event{};
			event.resourceId = inf::djb_hash(Definitions::MoneyResourceName);
			event.amount = digShaftCost;
			if (!handleAdjustResourceCommand(_context, event)) {
				std::cout << "Cannot afford " << digShaftCost << " to dig shaft." << std::endl;
				return false;
			}
		}

		return m_TerrainAlterationService.digShaft(_event.level);
	}

	bool GameCommandService::handleDigTileCommand(const GameCommand::CommandContext _context, const GameCommand::DigTileEvent& _event) const {
		return m_TerrainAlterationService.digTile(_event.level, _event.column);
	}

	bool GameCommandService::handleAdjustResourceCommand(const GameCommand::CommandContext _context, const GameCommand::AdjustResourceEvent& _event) const {
		if (!m_ResourceService.canAfford(_event.resourceId, _event.amount)) {
			return false;
		}

		m_ResourceService.payResourceId(_event.resourceId, _event.amount);
		
		return true;
	}

	bool GameCommandService::handleCreateJobCommand(const GameCommand::CommandContext _context, const GameCommand::CreateJobEvent& _event) const {
		if (!m_JobCreationService.canCreateJob(_event)) {
			return false;
		}

		m_JobCreationService.createJob(_event);

		return true;
	}

	bool GameCommandService::handleResetJobAllocationsCommand(const GameCommand::CommandContext _context, const GameCommand::ResetJobAllocationsEvent& _event) const {
		m_JobAllocationService.resetJobAllocations();
		return true;
	}

	bool GameCommandService::handleCreateWorkerCommand(const GameCommand::CommandContext _context, const GameCommand::CreateWorkerEvent& _event) const {
		if (!m_WorkerCreationService.canCreateWorker(_event)) {
			return false;
		}

		m_WorkerCreationService.createWorker(_event);
		return true;
	}

	bool GameCommandService::handleCreateShuttleCommand(const GameCommand::CommandContext _context, const GameCommand::CreateShuttleEvent& _event) const {
		if (!m_ShuttleCreationService.canCreateShuttle(_event)) {
			return false;
		}

		m_ShuttleCreationService.createShuttle(_event);
		return true;
	}
}
