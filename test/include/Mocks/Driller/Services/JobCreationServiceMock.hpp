#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_JOB_CREATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_JOB_CREATION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IJobCreationService.hpp>
#include <functional>

namespace drl {
	
	class JobCreationServiceMock : public IJobCreationService {
	public:
		~JobCreationServiceMock(void) override {}

		bool canCreateJob(const GameCommand::CreateJobEvent& _event) override {
			if (canCreateJobCallback) {
				return canCreateJobCallback(_event);
			}
			return false;
		}
		void createJob(const GameCommand::CreateJobEvent& _event) override {
			if (createJobCallback) {
				createJobCallback(_event);
			}
		}

		std::function<bool(const GameCommand::CreateJobEvent&)> canCreateJobCallback;
		std::function<void(const GameCommand::CreateJobEvent&)> createJobCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_JOB_CREATION_SERVICE_MOCK_HPP_