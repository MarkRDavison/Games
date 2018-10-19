#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_JOB_CREATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_JOB_CREATION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IJobCreationService.hpp>
#include <Utility/TestSignal.hpp>

namespace drl {
	
	class JobCreationServiceMock : public IJobCreationService {
	public:
		~JobCreationServiceMock(void) override {}

		bool canCreateJob(const GameCommand::CreateJobEvent& _event) override {
			return canCreateJobCallback(_event);
		}
		void createJob(const GameCommand::CreateJobEvent& _event) override {
			createJobCallback(_event);
		}
		void createJobsForPlacedBuilding(const BuildingPrototype& _prototype, const BuildingInstance& _buildingInstance) override {
			createJobsForPlacedBuildingCallback(_prototype, _buildingInstance);
		}

		inf::TestSignal<bool, const GameCommand::CreateJobEvent&> canCreateJobCallback;
		inf::TestSignal<void, const GameCommand::CreateJobEvent&> createJobCallback;
		inf::TestSignal<void, const BuildingPrototype&, const BuildingInstance&> createJobsForPlacedBuildingCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_JOB_CREATION_SERVICE_MOCK_HPP_