#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_JOB_COMPLETION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_JOB_COMPLETION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IJobCompletionService.hpp>
#include <functional>
#include <Utility/Hash.hpp>

namespace drl {
	
	class JobCompletionServiceMock : public IJobCompletionService {
	public:
		~JobCompletionServiceMock(void) override {}
		
		void handleJobCompleted(JobInstance& _jobInstance) override {
			if (handleJobCompletedCallback) {
				handleJobCompletedCallback(_jobInstance);
			}
		}

		void cleanupCompletedJobs(void) override {
			if (cleanupCompletedJobsCallback) {
				cleanupCompletedJobsCallback();
			}
		}

		void registerJobCompleteDelegate(const std::string& _prototypeId, const JobCompleteDelegate& _delegate) override {
			registerJobCompleteDelegate(inf::djb_hash(_prototypeId.c_str()), _delegate);
		}
		void registerJobCompleteDelegate(const JobPrototypeId& _prototypeId, const JobCompleteDelegate& _delegate) override {
			if (registerJobCompleteDelegateCallback) {
				registerJobCompleteDelegateCallback(_prototypeId, _delegate);
			}
		}
		bool isJobCompleteDelegateRegistered(const std::string& _prototypeId) override {
			return isJobCompleteDelegateRegistered(inf::djb_hash(_prototypeId.c_str()));
		}
		bool isJobCompleteDelegateRegistered(const JobPrototypeId& _prototypeId) override {
			if (isJobCompleteDelegateRegisteredCallback) {
				return isJobCompleteDelegateRegisteredCallback(_prototypeId);
			}
			return false;
		}
		JobCompleteDelegate& getJobCompleteDelegate(const std::string& _prototypeId) override {
			return getJobCompleteDelegate(inf::djb_hash(_prototypeId.c_str()));
		}
		JobCompleteDelegate& getJobCompleteDelegate(const JobPrototypeId& _prototypeId) override {
			if (getJobCompleteDelegateCallback) {
				return getJobCompleteDelegateCallback(_prototypeId);
			}
			return defaultJobCompleteDelegate;
		}

		std::function<void(JobInstance&)> handleJobCompletedCallback;
		std::function<void(void)> cleanupCompletedJobsCallback;
		std::function<void(const JobPrototypeId&, const JobCompleteDelegate&)> registerJobCompleteDelegateCallback;
		std::function<bool(const JobPrototypeId&)> isJobCompleteDelegateRegisteredCallback;
		std::function<JobCompleteDelegate&(const JobPrototypeId&)> getJobCompleteDelegateCallback;

		JobCompleteDelegate defaultJobCompleteDelegate;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_JOB_COMPLETION_SERVICE_MOCK_HPP_