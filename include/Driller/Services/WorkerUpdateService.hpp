#ifndef INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_

#include <Driller/Services/Interfaces/IWorkerUpdateService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Driller/DataStructures/WorkerData.hpp>

namespace drl {
	
	class WorkerUpdateService : public IWorkerUpdateService {
	public:
		WorkerUpdateService(WorkerData& _workerData, JobData& _jobData);
		~WorkerUpdateService(void) override;

		void update(float _delta) override;
		void updateWorker(WorkerInstance& _worker, float _delta);

		void updateIdleWorker(WorkerInstance& _worker, float _delta);
		void updateMovingToJobWorker(WorkerInstance& _worker, float _delta);

		void populatePath(WorkerInstance& _worker);
		void followPath(WorkerInstance& _worker, float _delta) const;

		JobInstance& retrieveJob(EntityId _jobId) ;
		const JobInstance& retrieveJob(EntityId _jobId) const;

	private:
		WorkerData& m_WorkerData;
		JobData& m_JobData;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_WORKER_UPDATE_SERVICE_HPP_