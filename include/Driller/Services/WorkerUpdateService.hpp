#ifndef INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_

#include <Driller/Services/Interfaces/IJobCompletionService.hpp>
#include <Driller/Services/Interfaces/INeedProviderLocationService.hpp>
#include <Driller/Services/Interfaces/IWorkerUpdateService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Driller/DataStructures/WorkerData.hpp>
#include <Driller/DataStructures/BuildingData.hpp>

namespace drl {
	
	class WorkerUpdateService : public IWorkerUpdateService {
	public:
		WorkerUpdateService(WorkerData& _workerData, BuildingData&  _buildingData, JobData& _jobData, IJobCompletionService& _jobCompletionService, INeedProviderLocationService& _needProviderLocationService);
		~WorkerUpdateService(void) override;

		void update(float _delta) override;
		void updateWorker(WorkerInstance& _worker, float _delta);

		void updateIdleWorker(WorkerInstance& _worker, float _delta);
		void updateMovingToNeedWorker(WorkerInstance& _worker, float _delta);
		void updateMovingToJobWorker(WorkerInstance& _worker, float _delta);
		void updateWorkingJobWorker(WorkerInstance& _worker, float _delta);
		void updateWorkerNeeds(WorkerInstance& _worker, float _delta);
		void updateRestoringNeedWorker(WorkerInstance& _worker, float _delta);

		void populatePath(WorkerInstance& _worker, const sf::Vector2i& _targetCoordinates, WorkerInstance::WorkerState _stateWhenTargetReached);
		void followPath(WorkerInstance& _worker, float _delta, WorkerInstance::WorkerState _stateWhenTargetReached) const;
		void sendTowardsNeedProvider(WorkerInstance& _worker, EntityId _needProviderId);

		static void resetWorkerAfterCompletingJob(WorkerInstance& _worker, const JobInstance& _jobInstance);

		JobInstance& retrieveJob(EntityId _jobId) ;
		const JobInstance& retrieveJob(EntityId _jobId) const;

		BuildingInstance& retrieveBuilding(EntityId _buildingId);
		const BuildingInstance& retrieveBuilding(EntityId _buildingId) const;

	private:
		WorkerData& m_WorkerData;
		BuildingData&  m_BuildingData;
		JobData& m_JobData;

		IJobCompletionService& m_JobCompletionService;
		INeedProviderLocationService& m_NeedProviderLocationService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_