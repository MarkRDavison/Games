#ifndef INCLUDED_DRILLER_SERVICE_GAME_COMMAND_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICE_GAME_COMMAND_SERVICE_HPP_

#include <Driller/Services/Interfaces/IGameCommandService.hpp>
#include <Driller/Services/Interfaces/IBuildingPlacementService.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Driller/Services/Interfaces/ITerrainAlterationService.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>
#include "Interfaces/IJobCreationService.hpp"
#include "Interfaces/IJobAllocationService.hpp"
#include "Interfaces/IWorkerCreationService.hpp"

namespace drl {
	
	class GameCommandService : public IGameCommandService {
	public:
		GameCommandService(inf::IResourceService& _resourceService, ITerrainAlterationService& _terrainAlterationService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, IJobCreationService& _jobCreationService, IJobPrototypeService& _jobPrototypeService, IJobAllocationService& _jobAllocationService, IWorkerCreationService& _workerCreationService, IWorkerPrototypeService& _workerPrototypeService);
		GameCommandService(inf::IResourceService& _resourceService, ITerrainAlterationService& _terrainAlterationService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, IJobCreationService& _jobCreationService, IJobPrototypeService& _jobPrototypeService, IJobAllocationService& _jobAllocationService, IWorkerCreationService& _workerCreationService, IWorkerPrototypeService& _workerPrototypeService, long long _startTick);
		~GameCommandService(void) override;

		void tick(void) override;
		long long getCurrentTick(void) const override;

		bool executeGameCommand(const GameCommand& _command) override;

	protected:
		bool handlePlaceBuildingCommand(const GameCommand::PlaceBuildingEvent& _event) const;
		bool handleDigShaftCommand(const GameCommand::DigShaftEvent& _event) const;
		bool handleDigTileCommand(const GameCommand::DigTileEvent& _event) const;
		bool handleAdjustResourceCommand(const GameCommand::AdjustResourceEvent& _event) const;
		bool handleCreateJobCommand(const GameCommand::CreateJobEvent& _event) const;
		bool handleResetJobAllocationsCommand(const GameCommand::ResetJobAllocationsEvent& _event) const;
		bool handleCreateWorkerCommand(const GameCommand::CreateWorkerEvent& _event) const;

	private:
		inf::IResourceService& m_ResourceService;
		ITerrainAlterationService& m_TerrainAlterationService;
		IBuildingPlacementService& m_BuildingPlacementService;
		IBuildingPrototypeService& m_BuildingPrototypeService;
		IJobCreationService& m_JobCreationService;
		IJobPrototypeService& m_JobPrototypeService;
		IJobAllocationService& m_JobAllocationService;
		IWorkerCreationService& m_WorkerCreationService;
		IWorkerPrototypeService& m_WorkerPrototypeService;

		long long m_CurrentTick;
	};

}

#endif // INCLUDED_DRILLER_SERVICE_ININCLUDED_DRILLER_SERVICE_GAME_COMMAND_SERVICE_HPP_TERFACES_I_GAME_COMMAND_SERVICE_HPP_