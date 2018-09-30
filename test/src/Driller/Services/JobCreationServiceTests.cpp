#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Driller/Services/JobCreationService.hpp>
#include <Mocks/Driller/Services/TerrainAlterationServiceMock.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>
#include <Driller/DataStructures/JobData.hpp>

namespace drl {
	namespace JobCreationServiceTests {
		
		TEST_CASE("canCreateJob for digging tile at location that has not been dug returns true", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = false;

			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId&) { return true; };
			terrainAlterationService.defaultTile = TerrainTile(tile);
			terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };
			
			REQUIRE(service.canCreateJob(event));
		}

		TEST_CASE("canCreateJob for digging tile at return false if the job prototype is not registered", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };
			
			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash("asd"); };
			bool isPrototypeRegisteredInvoked = false;
			jobPrototypeService.isPrototypeRegisteredByIdCallback = [&](const JobPrototypeId& _id) {
				isPrototypeRegisteredInvoked = true;
				REQUIRE(event.jobTypeId == _id);
				return false;
			};

			REQUIRE_FALSE(service.canCreateJob(event));
			REQUIRE(isPrototypeRegisteredInvoked);
		}

		TEST_CASE("canCreateJob for digging tile at location that has been dug returns false", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			TerrainTile tile{};
			tile.dugOut = true;
			tile.jobReserved = false;

			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId&) { return true; };
			terrainAlterationService.defaultTile = TerrainTile(tile);
			terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			REQUIRE_FALSE(service.canCreateJob(event));
		}

		TEST_CASE("canCreateJob for digging tile at location that has not been dug but has a job reserved returns false", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = true;

			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId&) { return true; };
			terrainAlterationService.defaultTile = TerrainTile(tile);
			terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			REQUIRE_FALSE(service.canCreateJob(event));
		}

		TEST_CASE("createJob for digging tile at location that has not been dug emplaces a job from the prototype as expected", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = true;

			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			terrainAlterationService.defaultTile = TerrainTile(tile);
			terrainAlterationService.doesTileExistCallback = [&](int, int) {
				return true;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			bool createInstanceInvoked = false;
			jobPrototypeService.createInstanceByIdCallback = [&](const JobPrototypeId& _id) {
				createInstanceInvoked = true;
				return JobInstance{};
			};

			service.createJob(event);

			REQUIRE(createInstanceInvoked);
			REQUIRE(1 == jobData.jobs.size());
			JobInstance& instance = jobData.jobs[0];

			REQUIRE(event.coordinates == instance.coordinates);
			REQUIRE(event.bounds == instance.bounds);
			REQUIRE(event.jobPerformOffset == instance.jobPerformOffset);
		}


		TEST_CASE("createJob for digging tile at location that has not been dug but exists correctly reserves a job on the tile in the terrain", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			TerrainTile tile{};
			tile.dugOut = false;
			tile.jobReserved = true;

			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			terrainAlterationService.defaultTile = TerrainTile(tile);
			terrainAlterationService.doesTileExistCallback = [&](int, int) { return true; };

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			bool reserveJobOnTileInvoked = false;
			terrainAlterationService.reserveJobOnTileCallback = [&](int _level, int _column) {
				REQUIRE(event.coordinates.y == _level);
				REQUIRE(event.coordinates.x == _column);
				reserveJobOnTileInvoked = true;
			};
			
			service.createJob(event);

			REQUIRE(reserveJobOnTileInvoked);
		}

		TEST_CASE("createJob for digging tile at location that has not been dug and does not exist correctly reserves a job on the tile in the terrain", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			terrainAlterationService.doesTileExistCallback = [&](int, int) { return false; };

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 0}, {1, 1}, {0.0f, 0.0f} };

			bool terrainTileReserved = false;
			terrainAlterationService.reserveJobOnTileCallback = [&](int _level, int _column) {
				REQUIRE(event.coordinates.y == _level);
				REQUIRE(event.coordinates.x == _column);
				terrainTileReserved = true;
			};

			service.createJob(event);

			REQUIRE(terrainTileReserved);
		}

		TEST_CASE("canCreateJob for digging tile at location on level that does not exist returns false", "[Driller][Services][JobCreationService]") {
			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobPrototypeServiceMock jobPrototypeService;
			JobCreationService service(jobData, terrainAlterationService, jobPrototypeService);

			jobPrototypeService.isPrototypeRegisteredByIdCallback = [](const JobPrototypeId& _id) { return true; };
			jobPrototypeService.getPrototypeIdCallback = [](const std::string& _prototypeName) { return inf::djb_hash(Definitions::JobPrototypeName_Dig); };
			terrainAlterationService.doesTileExistCallback = [&](int, int) { return false; };
			bool doesLevelExistInvoked = false;
			terrainAlterationService.doesLevelExistCallback = [&](int _level) {
				doesLevelExistInvoked = true;
				return false;
			};

			const GameCommand::CreateJobEvent event{ Definitions::JobPrototypeName_Dig, {1, 1}, {1, 1}, {0.0f, 0.0f} };

			REQUIRE_FALSE(service.canCreateJob(event));
			REQUIRE(doesLevelExistInvoked);
		}

	}
}
