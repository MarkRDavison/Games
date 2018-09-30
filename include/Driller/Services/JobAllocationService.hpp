#ifndef INCLUDED_DRILLER_SERVICES_JOB_ALLOCATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_JOB_ALLOCATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IJobAllocationService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Driller/DataStructures/WorkerData.hpp>
#include "Interfaces/ITerrainAlterationService.hpp"

namespace drl {
	
	class JobAllocationService : public IJobAllocationService {
	public:
		JobAllocationService(WorkerData& _workerData, JobData& _jobData, ITerrainAlterationService& _terrainAlterationService);
		~JobAllocationService(void) override;

		void resetJobAllocations(void) override;
		void allocateJobs(void) override;
		void allocateJobToWorker(WorkerInstance& _workerInstance) override;

		bool canWorkerPerformJobType(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) override;
		bool canWorkerAccessJob(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) override;

	private:
		WorkerData& m_WorkerData;
		JobData& m_JobData;
		ITerrainAlterationService& m_TerrainAlterationService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_JOB_ALLOCATION_SERVICE_HPP_