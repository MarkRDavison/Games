#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_JOB_ALLOCATION_SERVICE_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_JOB_ALLOCATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IJobAllocationService.hpp>
#include <functional>

namespace drl {
	
	class JobAllocationServiceMock : public IJobAllocationService {
	public:
		~JobAllocationServiceMock(void) override {}

		void resetJobAllocations(void) override {
			if (resetJobAllocationsCallback) {
				resetJobAllocationsCallback();
			}
		}
		void allocateJobs(void) override {
			if (allocateJobsCallback) {
				allocateJobsCallback();
			}
		}
		void allocateJobToWorker(WorkerInstance& _workerInstance) override {
			if (allocateJobToWorkerCallback) {
				allocateJobToWorkerCallback(_workerInstance);
			}
		}

		bool canWorkerPerformJobType(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) override {
			if (canWorkerPerformJobCallback) {
				return canWorkerPerformJobCallback(_workerInstance, _jobInstance);
			}
			return false;
		}
		bool canWorkerAccessJob(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) override {
			if (canWorkerAccessJobCallback) {
				return canWorkerAccessJobCallback(_workerInstance, _jobInstance);
			}
			return false;
		}

		std::function<void(void)> resetJobAllocationsCallback;
		std::function<void(void)> allocateJobsCallback;
		std::function<void(WorkerInstance&)> allocateJobToWorkerCallback;

		std::function<bool(const WorkerInstance&, const JobInstance&)> canWorkerPerformJobCallback;
		std::function<bool(const WorkerInstance&, const JobInstance&)> canWorkerAccessJobCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_JOB_ALLOCATION_SERVICE_HPP_