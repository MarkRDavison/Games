#include <Driller/Services/JobAllocationService.hpp>

namespace drl {

	JobAllocationService::JobAllocationService(WorkerData& _workerData, JobData& _jobData, ITerrainAlterationService& _terrainAlterationService) :
		m_WorkerData(_workerData),
		m_JobData(_jobData),
		m_TerrainAlterationService(_terrainAlterationService) {
		
	}

	JobAllocationService::~JobAllocationService(void) {
		
	}

	void JobAllocationService::resetJobAllocations(void) {
		for (WorkerInstance& _worker : m_WorkerData.workers) {
			_worker.hasAllocatedJob = false;
			_worker.allocatedJobId = { 0u };
		}
		for (JobInstance& _job : m_JobData.jobs) {
			_job.allocated = false;
			_job.allocatedWorkerId = { 0u };
		}
	}

	void JobAllocationService::allocateJobs(void) {
		for (WorkerInstance& _worker : m_WorkerData.workers) {
			allocateJobToWorker(_worker);
		}
	}

	void JobAllocationService::allocateJobToWorker(WorkerInstance& _workerInstance) {
		for (JobInstance& _job : m_JobData.jobs) {
			if (canWorkerPerformJobType(_workerInstance, _job)) {
				_workerInstance.hasAllocatedJob = true;
				_workerInstance.allocatedJobId = _job.Id;
				_job.allocated = true;
				_job.allocatedWorkerId = _workerInstance.Id;
				return;
			}
		}
	}

	bool JobAllocationService::canWorkerPerformJobType(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) {
		if (_workerInstance.hasAllocatedJob) {
			return false;
		}

		for (const JobPrototypeId& _validId : _workerInstance.validJobTypes) {
			if (!_jobInstance.allocated && 
				_validId == _jobInstance.prototypeId &&
				canWorkerAccessJob(_workerInstance, _jobInstance)) {
				return true;
			}
		}

		return false;
	}

	bool JobAllocationService::canWorkerAccessJob(const WorkerInstance& _workerInstance, const JobInstance& _jobInstance) {
		const int Level = _jobInstance.coordinates.y;
		if (!m_TerrainAlterationService.doesLevelExist(Level)) {
			return false;
		}

		if (_jobInstance.coordinates.x > 0) {
			for (int col = 1; col < _jobInstance.coordinates.x; ++col) {
				if (!m_TerrainAlterationService.isTileDugOut(Level, col)) {
					return false;
				}
			}
		}
		if (_jobInstance.coordinates.x < 0) {
			for (int col = -1; col > _jobInstance.coordinates.x; --col) {
				if (!m_TerrainAlterationService.isTileDugOut(Level, col)) {
					return false;
				}
			}
		}

		return true;
	}

}
