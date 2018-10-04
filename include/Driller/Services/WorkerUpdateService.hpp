#ifndef INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_

#include <Driller/Services/Interfaces/IWorkerUpdateService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Driller/DataStructures/WorkerData.hpp>
#include "Interfaces/IJobCompletionService.hpp"

namespace drl {
	
	class WorkerUpdateService : public IWorkerUpdateService {
	public:
		WorkerUpdateService(WorkerData& _workerData, JobData& _jobData, IJobCompletionService& _jobCompletionService);
		~WorkerUpdateService(void) override;

		void update(float _delta) override;
		void updateWorker(WorkerInstance& _worker, float _delta);

		void updateIdleWorker(WorkerInstance& _worker, float _delta);
		void updateMovingToJobWorker(WorkerInstance& _worker, float _delta);
		void updateWorkingJobWorker(WorkerInstance& _worker, float _delta);

		void populatePath(WorkerInstance& _worker);
		void followPath(WorkerInstance& _worker, float _delta) const;

		static void resetWorkerAfterCompletingJob(WorkerInstance& _worker, const JobInstance& _jobInstance);

		JobInstance& retrieveJob(EntityId _jobId) ;
		const JobInstance& retrieveJob(EntityId _jobId) const;

	private:
		WorkerData& m_WorkerData;
		JobData& m_JobData;

		IJobCompletionService& m_JobCompletionService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_