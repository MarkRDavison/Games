#include <Driller/Services/JobCreationService.hpp>
#include <Driller/DataStructures/TerrainTile.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Sol2/sol.hpp>

namespace drl {

	JobCreationService::JobCreationService(JobData& _jobData, ITerrainAlterationService& _terrainAlterationService, IJobPrototypeService& _jobPrototypeService, IBuildingPlacementService& _buildingPlacementService, IBuildingPrototypeService& _buildingPrototypeService, inf::IResourceService& _resourceService) :
		m_JobData(_jobData),
		m_TerrainAlterationService(_terrainAlterationService),
		m_JobPrototypeService(_jobPrototypeService),
		m_BuildingPlacementService(_buildingPlacementService),
		m_BuildingPrototypeService(_buildingPrototypeService),
		m_ResourceService(_resourceService) {
		
	}

	JobCreationService::~JobCreationService(void) {
		
	}

	bool JobCreationService::canCreateJob(const GameCommand::CreateJobEvent& _event) {
		// TODO: Do we need to register custom prototypes for whether job can be created and creating the job?
		// Like, register for this job type we call this method to see if we can make it, and another one when we actually create it
		// For now have multiple methods in this service for each job type

		if (!m_JobPrototypeService.isPrototypeRegistered(_event.jobTypeId)) {
			return false;
		}

		if (_event.jobTypeId == m_JobPrototypeService.getPrototypeId(Definitions::JobPrototypeName_Dig)) {
			return canCreateDigTileJob(_event);
		}

		if (_event.jobTypeId == m_JobPrototypeService.getPrototypeId(Definitions::JobPrototypeName_BuildBuilding)) {
			return canCreateBuildBuildingJob(_event);
		}

		throw std::runtime_error("Job Prototype does not have a specific canCreateJob implementation");
	}
	void JobCreationService::createJob(const GameCommand::CreateJobEvent& _event) {
		if (_event.jobTypeId == m_JobPrototypeService.getPrototypeId(Definitions::JobPrototypeName_Dig)) {
			createDigTileJob(_event);
			return;
		}

		if (_event.jobTypeId == m_JobPrototypeService.getPrototypeId(Definitions::JobPrototypeName_BuildBuilding)) {
			createBuildBuildingJob(_event);
			return;
		}

		throw std::runtime_error("Job Prototype does not have a specific createJob implementation");
	}

	bool JobCreationService::canCreateDigTileJob(const GameCommand::CreateJobEvent& _event) const {
		if (!m_TerrainAlterationService.doesTileExist(_event.coordinates.y, _event.coordinates.x)) {
			if (!m_TerrainAlterationService.doesLevelExist(_event.coordinates.y)) {
				return false;
			}
			return true;
		}

		const TerrainTile& tile = m_TerrainAlterationService.getTile(_event.coordinates.y, _event.coordinates.x);

		return !tile.dugOut && !tile.jobReserved;
	}

	void JobCreationService::createDigTileJob(const GameCommand::CreateJobEvent& _event) const {
		m_TerrainAlterationService.initialiseTile(_event.coordinates.y, _event.coordinates.x);
		m_TerrainAlterationService.reserveJobOnTile(_event.coordinates.y, _event.coordinates.x, true);

		JobInstance& instance = m_JobData.jobs.emplace_back(m_JobPrototypeService.createInstance(_event.jobTypeId));
		instance.coordinates = _event.coordinates;
		instance.bounds = _event.bounds;
		instance.jobPerformOffset = _event.jobPerformOffset;
		instance.prototypeId = _event.jobTypeId;
	}

	bool JobCreationService::canCreateBuildBuildingJob(const GameCommand::CreateJobEvent& _event) const {
		return m_BuildingPlacementService.canPlacePrototype(GameCommand::CommandContext::CreatingJob, _event.additionalPrototypeId, _event.coordinates.y, _event.coordinates.x);
	}
	void JobCreationService::createBuildBuildingJob(const GameCommand::CreateJobEvent& _event) const {
		m_TerrainAlterationService.initialiseTile(_event.coordinates.y, _event.coordinates.x);
		m_TerrainAlterationService.reserveJobOnTile(_event.coordinates.y, _event.coordinates.x, true);
		
		const BuildingPrototype& prototype = m_BuildingPrototypeService.getPrototype(_event.additionalPrototypeId);
		m_ResourceService.payResourceBundle(prototype.cost);
		JobInstance& instance = m_JobData.jobs.emplace_back(m_JobPrototypeService.createInstance(_event.jobTypeId));
		instance.coordinates = _event.coordinates;
		instance.bounds = _event.bounds;
		instance.jobPerformOffset = _event.jobPerformOffset;
		instance.prototypeId = _event.jobTypeId;
		instance.additionalPrototypeId = _event.additionalPrototypeId;
	}

	void JobCreationService::createJobsForPlacedBuilding(const BuildingPrototype& _prototype, const BuildingInstance& _buildingInstance) {
		if (!_prototype.providesJobs) {
			return;
		}

		for (const BuildingProvidedJob& providedJob : _prototype.providedJobs) {
			JobInstance& instance = m_JobData.jobs.emplace_back(m_JobPrototypeService.createInstance(providedJob.prototypeId));
			instance.coordinates = _buildingInstance.coordinates + providedJob.location;
		}
	}

}
