#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_COMPLETION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_COMPLETION_SERVICE_HPP_

#include <Driller/DataStructures/JobInstance.hpp>
#include <Driller/DataStructures/JobCompleteDelegate.hpp>

namespace drl {
	
	class IJobCompletionService {
	public:
		virtual ~IJobCompletionService(void) = 0;

		virtual void handleJobCompleted(JobInstance& _jobInstance) = 0;
		virtual void cleanupCompletedJobs(void) = 0;

		virtual void registerJobCompleteDelegate(const std::string& _prototypeId, const JobCompleteDelegate& _delegate) = 0;
		virtual void registerJobCompleteDelegate(const JobPrototypeId& _prototypeId, const JobCompleteDelegate& _delegate) = 0;

		virtual bool isJobCompleteDelegateRegistered(const std::string& _prototypeId) = 0;
		virtual bool isJobCompleteDelegateRegistered(const JobPrototypeId& _prototypeId) = 0;

		virtual JobCompleteDelegate& getJobCompleteDelegate(const std::string& _prototypeId) = 0;
		virtual JobCompleteDelegate& getJobCompleteDelegate(const JobPrototypeId& _prototypeId) = 0;
	};

	inline IJobCompletionService::~IJobCompletionService(void) = default;
}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_COMPLETION_SERVICE_HPP_