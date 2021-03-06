#ifndef INCLUDED_DRILLER_SERVICES_JOB_CREATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_JOB_CREATION_SERVICE_HPP_

#include <Driller/DataStructures/JobData.hpp>
#include <Driller/Services/Interfaces/ICostService.hpp>
#include <Driller/Services/Interfaces/IJobCreationService.hpp>
#include <Driller/Services/Interfaces/ITerrainAlterationService.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Driller/Services/Interfaces/IBuildingPlacementService.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>

namespace drl {
	
	class JobCreationService : public IJobCreationService {
	public:
		JobCreationService(JobData& _jobData, ITerrainAlterationService& _terrainAlterationService, IJobPrototypeService& _jobPrototypeService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, ICostService& _costService, inf::IResourceService& _resourceService);
		~JobCreationService(void) override;

		bool canCreateJob(const GameCommand::CreateJobEvent& _event) override;
		void createJob(const GameCommand::CreateJobEvent& _event) override;

		bool canCreateDigTileJob(const GameCommand::CreateJobEvent& _event) const;
		void createDigTileJob(const GameCommand::CreateJobEvent& _event) const;

		bool canCreateBuildBuildingJob(const GameCommand::CreateJobEvent& _event) const;
		void createBuildBuildingJob(const GameCommand::CreateJobEvent& _event) const;

		void createJobsForPlacedBuilding(const BuildingPrototype& _prototype, const BuildingInstance& _buildingInstance) override;

	private:
		JobData& m_JobData;
		ITerrainAlterationService& m_TerrainAlterationService;
		IJobPrototypeService& m_JobPrototypeService;
		IBuildingPlacementService& m_BuildingPlacementService;
		IBuildingPrototypeService& m_BuildingPrototypeService;
		ICostService& m_CostService;
		inf::IResourceService& m_ResourceService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_JOB_CREATION_SERVICE_HPP_