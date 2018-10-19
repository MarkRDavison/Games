#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_CREATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_CREATION_SERVICE_HPP_

#include <Driller/DataStructures/GameCommand.hpp>
#include <Driller/DataStructures/BuildingInstance.hpp>
#include <Driller/DataStructures/BuildingPrototype.hpp>

namespace drl {
	
	class IJobCreationService {
	public:
		virtual ~IJobCreationService(void) = 0 {}

		virtual bool canCreateJob(const GameCommand::CreateJobEvent& _event) = 0;
		virtual void createJob(const GameCommand::CreateJobEvent& _event) = 0;

		virtual void createJobsForPlacedBuilding(const BuildingPrototype& _prototype, const BuildingInstance& _buildingInstance) = 0;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_JOB_CREATION_SERVICE_HPP_