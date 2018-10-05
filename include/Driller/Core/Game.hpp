#ifndef INCLUDED_DRILLER_CORE_GAME_HPP_
#define INCLUDED_DRILLER_CORE_GAME_HPP_

#include <Driller/Services/Interfaces/IGameCommandService.hpp>

#include <Driller/DataStructures/BuildingData.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Driller/DataStructures/TerrainData.hpp>
#include <Driller/DataStructures/WorkerData.hpp>
#include <Driller/Services/Interfaces/IJobAllocationService.hpp>
#include <Driller/Services/Interfaces/IWorkerUpdateService.hpp>
#include <Driller/Services/Interfaces/IJobCompletionService.hpp>
#include <Driller/Services/Interfaces/IShuttleDepartureService.hpp>
#include <Driller/Services/Interfaces/IShuttleUpdateService.hpp>
#include <Driller/Services/Interfaces/IShuttleCompletionService.hpp>

namespace drl {
	
	class Game {
	public:
		Game(IGameCommandService& _gameCommandService, IJobAllocationService& _jobAllocationService, IJobCompletionService& _jobCompletionService, IWorkerUpdateService& _workerUpdateService, IShuttleDepartureService& _shuttleDepartureService, IShuttleUpdateService& _shuttleUpdateService, IShuttleCompletionService& _shuttleCompletionService, TerrainData& _terrainData, BuildingData& _buildingData, JobData& _jobData, WorkerData& _workerData);
		~Game(void);

		void update(float _delta) const;

	private:
		IGameCommandService& m_GameCommandService;

		IJobAllocationService& m_JobAllocationService;
		IJobCompletionService& m_JobCompletionService;

		IWorkerUpdateService& m_WorkerUpdateService;

		IShuttleDepartureService& m_ShuttleDepartureService;
		IShuttleUpdateService& m_ShuttleUpdateService;
		IShuttleCompletionService& m_ShuttleCompletionService;

		TerrainData& m_TerrainData;
		BuildingData& m_BuildingData;
		JobData& m_JobData;
		WorkerData& m_WorkerData;
	};

}

#endif //INCLUDED_DRILLER_CORE_GAME_HPP_