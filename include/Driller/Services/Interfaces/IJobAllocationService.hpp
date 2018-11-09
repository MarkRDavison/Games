#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_ALLOCATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_ALLOCATION_SERVICE_HPP_

#include <Driller/DataStructures/JobInstance.hpp>
#include <Driller/DataStructures/WorkerInstance.hpp>

namespace drl {
	
	class IJobAllocationService {
	public:
		virtual ~IJobAllocationService(void) = 0;

		virtual void resetJobAllocations(void) = 0;
		virtual void allocateJobs(void) = 0;
		virtual void allocateJobToWorker(WorkerInstance& _workerInstance) = 0;

		virtual bool canWorkerPerformJobType(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) = 0;
		virtual bool canWorkerAccessJob(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) = 0;
	};

	inline IJobAllocationService::~IJobAllocationService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_ALLOCATION_SERVICE_HPP_