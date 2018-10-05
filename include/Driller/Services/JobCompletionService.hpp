#ifndef INCLUDED_DRILLER_SERVICES_JOB_COMPLETION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_JOB_COMPLETION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IJobCompletionService.hpp>
#include <Driller/Services/Interfaces/ITerrainAlterationService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <map>

namespace drl {
	
	class JobCompletionService : public IJobCompletionService {
	public:
		JobCompletionService(JobData& _jobData, ITerrainAlterationService& _terrainAlterationService);
		~JobCompletionService(void) override;

		void handleJobCompleted(JobInstance& _jobInstance) override;
		void cleanupCompletedJobs() override;
		void registerJobCompleteDelegate(const std::string& _prototypeId, const JobCompleteDelegate& _delegate) override;
		void registerJobCompleteDelegate(const JobPrototypeId& _prototypeId, const JobCompleteDelegate& _delegate) override;
		bool isJobCompleteDelegateRegistered(const std::string& _prototypeId) override;
		bool isJobCompleteDelegateRegistered(const JobPrototypeId& _prototypeId) override;
		JobCompleteDelegate& getJobCompleteDelegate(const std::string& _prototypeId) override;
		JobCompleteDelegate& getJobCompleteDelegate(const JobPrototypeId& _prototypeId) override;

	private:
		bool m_JobCompleted{ false };
		JobData& m_JobData;
		std::map<JobPrototypeId, JobCompleteDelegate> m_DelegateMap;

		ITerrainAlterationService& m_TerrainAlterationService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_JOB_COMPLETION_SERVICE_HPP_