#include <Driller/Core/Game.hpp>

namespace drl {

	Game::Game(IGameCommandService& _gameCommandService, IJobAllocationService& _jobAllocationService, IJobCompletionService& _jobCompletionService, IWorkerUpdateService& _workerUpdateService, TerrainData& _terrainData, BuildingData& _buildingData, JobData& _jobData, WorkerData& _workerData) :
		m_GameCommandService(_gameCommandService),
		m_JobAllocationService(_jobAllocationService),
		m_JobCompletionService(_jobCompletionService),
		m_WorkerUpdateService(_workerUpdateService),
		m_TerrainData(_terrainData),
		m_BuildingData(_buildingData),
		m_JobData(_jobData),
		m_WorkerData(_workerData) {
		
	}

	Game::~Game(void) {
		
	}

	void Game::update(float _delta) const {
		m_WorkerUpdateService.update(_delta);
		m_JobAllocationService.allocateJobs();
		m_JobCompletionService.cleanupCompletedJobs();
	}

}
