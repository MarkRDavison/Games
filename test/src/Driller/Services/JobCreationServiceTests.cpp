#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Driller/Services/JobCreationService.hpp>
#include <Mocks/Driller/Services/TerrainAlterationServiceMock.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Mocks/Driller/Services/BuildingPlacementServiceMock.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>

namespace drl {
	namespace JobCreationServiceTests {

		struct ServicePackage {
			ServicePackage() :
				service(jobData, terrainAlterationService, jobPrototypeService, buildingPlacementService, buildingPrototypeService, resourceService) {
				
			}

			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			BuildingPlacementServiceMock buildingPlacementService;
			BuildingPrototypeServiceMock buildingPrototypeService;
			inf::ResourceServiceMock resourceService;
			JobCreationService service;
		};
		
		TEST_CASE("canCreateJob for digging tile at location that has not been dug returns true", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = false;

			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			package.jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId&) { return true; };
			package.terrainAlterationService.defaultTile = TerrainTile(tile);
			package.terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };
			
			REQUIRE(package.service.canCreateJob(event));
		}

		TEST_CASE("canCreateJob for digging tile at return false if the job prototype is not registered", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };
			
			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash("asd"); };
			bool isPrototypeRegisteredInvoked = false;
			package.jobPrototypeService.isPrototypeRegisteredByIdCallback = [&](const JobPrototypeId& _id) {
				isPrototypeRegisteredInvoked = true;
				REQUIRE(event.jobTypeId == _id);
				return false;
			};

			REQUIRE_FALSE(package.service.canCreateJob(event));
			REQUIRE(isPrototypeRegisteredInvoked);
		}

		TEST_CASE("canCreateJob for digging tile at location that has been dug returns false", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			TerrainTile tile{};
			tile.dugOut = true;
			tile.jobReserved = false;

			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			package.jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId&) { return true; };
			package.terrainAlterationService.defaultTile = TerrainTile(tile);
			package.terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			REQUIRE_FALSE(package.service.canCreateJob(event));
		}

		TEST_CASE("canCreateJob for digging tile at location that has not been dug but has a job reserved returns false", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = true;

			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			package.jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId&) { return true; };
			package.terrainAlterationService.defaultTile = TerrainTile(tile);
			package.terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			REQUIRE_FALSE(package.service.canCreateJob(event));
		}

		TEST_CASE("createJob for digging tile at location that has not been dug emplaces a job from the prototype as expected", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = true;

			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			package.terrainAlterationService.defaultTile = TerrainTile(tile);
			package.terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			bool createInstanceInvoked = false;
			package.jobPrototypeService.createInstanceByIdCallback = [&](const JobPrototypeId& _id) {
				createInstanceInvoked = true;
				return JobInstance{};
			};

			package.service.createJob(event);

			REQUIRE(createInstanceInvoked);
			REQUIRE(1 == package.jobData.jobs.size());
			JobInstance& instance = package.jobData.jobs[0];

			REQUIRE(event.coordinates == instance.coordinates);
			REQUIRE(event.bounds == instance.bounds);
			REQUIRE(event.jobPerformOffset == instance.jobPerformOffset);
		}


		TEST_CASE("createJob for digging tile at location that has not been dug but exists correctly reserves a job on the tile in the terrain", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = true;

			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			package.terrainAlterationService.defaultTile = TerrainTile(tile);
			package.terrainAlterationService.doesTileExistCallback = [&](int, int) { return true; };

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			bool reserveJobOnTileInvoked = false;
			package.terrainAlterationService.reserveJobOnTileCallback = [&](int _level, int _column, bool _jobReserved) {
				REQUIRE(event.coordinates.y == _level);
				REQUIRE(event.coordinates.x == _column);
				REQUIRE(_jobReserved);
				reserveJobOnTileInvoked = true;
			};
			
			package.service.createJob(event);

			REQUIRE(reserveJobOnTileInvoked);
		}

		TEST_CASE("createJob for digging tile at location that has not been dug and does not exist correctly reserves a job on the tile in the terrain", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			package.terrainAlterationService.doesTileExistCallback = [&](int, int) { return false; };

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			bool terrainTileReserved = false;
			package.terrainAlterationService.reserveJobOnTileCallback = [&](int _level, int _column, bool _jobReserved) {
				REQUIRE(event.coordinates.y == _level);
				REQUIRE(event.coordinates.x == _column);
				REQUIRE(_jobReserved);
				terrainTileReserved = true;
			};

			package.service.createJob(event);

			REQUIRE(terrainTileReserved);
		}

		TEST_CASE("canCreateJob for digging tile at location on level that does not exist returns false", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			package.jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId& _id) { return true; };
			package.jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			package.terrainAlterationService.doesTileExistCallback = [&](int, int) { return false; };
			bool doesLevelExistInvoked = false;
			package.terrainAlterationService.doesLevelExistCallback = [&](int _level) {
				doesLevelExistInvoked = true;
				return false;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 1}, {1, 1}, {0.0f, 0.0f} };

			REQUIRE_FALSE(package.service.canCreateJob(event));
			REQUIRE(doesLevelExistInvoked);
		}

		TEST_CASE("canCreateBuildBuildingJob invokes the building placement service with the correct protoype id", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			BuildingPrototypeId Id{ 1u };
			const sf::Vector2i PlaceCoordinates{ 1,2 };

			GameCommand::CreateJobEvent event{};
			event.coordinates = PlaceCoordinates;
			event.additionalPrototypeId = Id;

			bool canPlacePrototypeInvoked = false;
			package.buildingPlacementService.canPlacePrototypeCallback = [&](GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _event) {
				REQUIRE(Id == _event.prototypeId);
				REQUIRE(PlaceCoordinates.y == _event.level);
				REQUIRE(PlaceCoordinates.x == _event.column);
				canPlacePrototypeInvoked = true;
				return false;
			};

			REQUIRE_FALSE(package.service.canCreateBuildBuildingJob(event));
			REQUIRE(canPlacePrototypeInvoked);
		}

		TEST_CASE("createBuildBuildingJob emplaces the job correctly", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			BuildingPrototypeId Id{ 1u };
			const sf::Vector2i PlaceCoordinates{ 1,2 };

			GameCommand::CreateJobEvent event{};
			event.coordinates = PlaceCoordinates;
			event.additionalPrototypeId = Id;

			package.service.createBuildBuildingJob(event);

			REQUIRE(1 == package.jobData.jobs.size());
			JobInstance& job = package.jobData.jobs[0];
			REQUIRE(Id == job.additionalPrototypeId);
			REQUIRE(PlaceCoordinates == job.coordinates);
		}

		TEST_CASE("createBuildBuildingJob gets the building prototype and pays the resource cost", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			BuildingPrototypeId Id{ 1u };
			const sf::Vector2i PlaceCoordinates{ 1,2 };
			BuildingPrototype buildingPrototype{};

			GameCommand::CreateJobEvent event{};
			event.coordinates = PlaceCoordinates;
			event.additionalPrototypeId = Id;

			bool getPrototypeByIdCallbackInvoked = false;
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) -> const BuildingPrototype& { 
				getPrototypeByIdCallbackInvoked = true;
				return buildingPrototype; 
			};

			bool payResourceBundleCallbackInvoked = false;
			package.resourceService.payResourceBundleCallback = [&](const inf::ResourceBundle& _resourceBundle) -> void {
				REQUIRE(&buildingPrototype.cost == &_resourceBundle);
				payResourceBundleCallbackInvoked = true;
			};

			package.service.createBuildBuildingJob(event);

			REQUIRE(getPrototypeByIdCallbackInvoked);
			REQUIRE(payResourceBundleCallbackInvoked);
		}


		TEST_CASE("createJobsForPlacedBuilding emplaces jobs as exected", "[Driller][Services][JobCreationService]") {
			ServicePackage package{};

			BuildingInstance instance{};
			instance.coordinates = { 0,0 };
			BuildingPrototype prototype{};
			prototype.providesJobs = true;

			const JobPrototypeId jobId = { 1u };

			{
				BuildingProvidedJob& job = prototype.providedJobs.emplace_back();
				job.location = { 0,0 };
				job.prototypeId = jobId;
			}
			{
				BuildingProvidedJob& job = prototype.providedJobs.emplace_back();
				job.location = { 1,0 };
				job.prototypeId = jobId;
			}
			{
				BuildingProvidedJob& job = prototype.providedJobs.emplace_back();
				job.location = { 2,0 };
				job.prototypeId = jobId;
			}

			package.service.createJobsForPlacedBuilding(prototype, instance);

			REQUIRE(prototype.providedJobs.size() == package.jobData.jobs.size());

			for (unsigned i = 0; i < prototype.providedJobs.size(); ++i) {
				REQUIRE(prototype.providedJobs[i].location == package.jobData.jobs[i].coordinates);
			}
		}
	}
}
