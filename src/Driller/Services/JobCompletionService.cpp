#include <Driller/Services/JobCompletionService.hpp>
#include <Utility/Hash.hpp>
#include <algorithm>

namespace drl {

	JobCompletionService::JobCompletionService(JobData& _jobData, ITerrainAlterationService& _terrainAlterationService) :
		m_JobData(_jobData),
		m_TerrainAlterationService(_terrainAlterationService) {
		
	}

	JobCompletionService::~JobCompletionService(void) {
		
	}

	void JobCompletionService::handleJobCompleted(JobInstance& _jobInstance) {
		_jobInstance.removalRequired = true;
		_jobInstance.allocated = false;
		_jobInstance.allocatedWorkerId = 0u;
		m_TerrainAlterationService.reserveJobOnTile(_jobInstance.coordinates.y, _jobInstance.coordinates.x, false); // TODO: This and creating jobs needs to do this for all tiles in the job
		m_JobCompleted = true;
	}

	void JobCompletionService::cleanupCompletedJobs(void) {
		if (m_JobCompleted) {
			m_JobCompleted = false;
			m_JobData.jobs.erase(std::remove_if(m_JobData.jobs.begin(), m_JobData.jobs.end(), [](const JobInstance& _jobInstance) {
				return _jobInstance.removalRequired;
			}), m_JobData.jobs.end());
		}
	}

	void JobCompletionService::registerJobCompleteDelegate(const std::string& _prototypeId, const JobCompleteDelegate& _delegate) {
		registerJobCompleteDelegate(inf::djb_hash(_prototypeId.c_str()), _delegate);
	}
	void JobCompletionService::registerJobCompleteDelegate(const JobPrototypeId& _prototypeId, const JobCompleteDelegate& _delegate) {
		m_DelegateMap[_prototypeId] = _delegate;
	}

	bool JobCompletionService::isJobCompleteDelegateRegistered(const std::string& _prototypeId) {
		return isJobCompleteDelegateRegistered(inf::djb_hash(_prototypeId.c_str()));
	}
	bool JobCompletionService::isJobCompleteDelegateRegistered(const JobPrototypeId& _prototypeId) {
		return m_DelegateMap.find(_prototypeId) != m_DelegateMap.end();
	}

	JobCompleteDelegate& JobCompletionService::getJobCompleteDelegate(const std::string& _prototypeId) {
		return getJobCompleteDelegate(inf::djb_hash(_prototypeId.c_str()));
	}
	JobCompleteDelegate& JobCompletionService::getJobCompleteDelegate(const JobPrototypeId& _prototypeId) {
		return m_DelegateMap[_prototypeId];
	}

}
