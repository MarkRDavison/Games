#ifndef INCLUDED_DRILLER_SERVICES_JOB_CREATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_JOB_CREATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IJobCreationService.hpp>
#include <Driller/Services/Interfaces/ITerrainAlterationService.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include "Interfaces/IBuildingPlacementService.hpp"

namespace drl {
	
	class JobCreationService : public IJobCreationService {
	public:
		JobCreationService(JobData& _jobData, ITerrainAlterationService& _terrainAlterationService, IJobPrototypeService& _jobPrototypeService, IBuildingPlacementService& _buildingPlacementService);
		~JobCreationService(void) override;

		bool canCreateJob(const GameCommand::CreateJobEvent& _event) override;
		void createJob(const GameCommand::CreateJobEvent& _event) override;

		bool canCreateDigTileJob(const GameCommand::CreateJobEvent& _event) const;
		void createDigTileJob(const GameCommand::CreateJobEvent& _event) const;

		bool canCreateBuildBuildingJob(const GameCommand::CreateJobEvent& _event) const;
		void createBuildBuildingJob(const GameCommand::CreateJobEvent& _event) const;

	private:
		JobData& m_JobData;
		ITerrainAlterationService& m_TerrainAlterationService;
		IJobPrototypeService& m_JobPrototypeService;
		IBuildingPlacementService& m_BuildingPlacementService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_JOB_CREATION_SERVICE_HPP_