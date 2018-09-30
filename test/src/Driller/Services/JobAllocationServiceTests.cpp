#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Utility/Hash.hpp>
#include <Driller/Services/JobAllocationService.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Mocks/Driller/Services/TerrainAlterationServiceMock.hpp>

namespace drl {
	namespace JobAllocationServiceTests {
		
		TEST_CASE("allocating job to a worker does nothing if there are no jobs", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };

			WorkerInstance worker{};

			REQUIRE_NOTHROW(service.allocateJobToWorker(worker));
			REQUIRE_FALSE(worker.hasAllocatedJob);
		}

		TEST_CASE("canWorkerPerformJob returns true when worker can perform job", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;

			REQUIRE(service.canWorkerPerformJobType(worker, job));
		}

		TEST_CASE("canWorkerPerformJob returns false when worker cannot perform job", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId + 1;

			REQUIRE_FALSE(service.canWorkerPerformJobType(worker, job));
		}

		TEST_CASE("canWorkerPerformJob returns false when worker already has an allocated job", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			worker.hasAllocatedJob = true;
			JobInstance job{};
			job.prototypeId = JobId;

			REQUIRE_FALSE(service.canWorkerPerformJobType(worker, job));
		}

		TEST_CASE("canWorkerPerformJob returns false when job already has been allocated", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			worker.Id = 1u;
			JobInstance job{};
			job.prototypeId = JobId;
			job.allocated = true;

			REQUIRE_FALSE(service.canWorkerPerformJobType(worker, job));
		}

		TEST_CASE("allocateJobToWorker allocates on the worker and the job", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.Id = { 1u };
			worker.validJobTypes = { JobId };
			JobInstance& job = jobData.jobs.emplace_back();
			job.prototypeId = JobId;
			job.Id = { 2u };

			service.allocateJobToWorker(worker);

			REQUIRE(worker.hasAllocatedJob);
			REQUIRE(worker.Id == job.allocatedWorkerId);
			REQUIRE(job.allocated);
			REQUIRE(job.Id == worker.allocatedJobId);
		}

		TEST_CASE("canWorkerAccessJob returns false when the job coordinates are at a level that has not been dug out", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			const sf::Vector2i Coordinates{ 5,1 };

			bool doesLevelExistInvoked = false;
			terrainAlterationService.doesLevelExistCallback = [&](int) {
				doesLevelExistInvoked = true;
				return false;
			};

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;
			job.coordinates = Coordinates;
			
			REQUIRE_FALSE(service.canWorkerAccessJob(worker, job));
			REQUIRE(doesLevelExistInvoked);
		}

		TEST_CASE("canWorkerAccessJob returns false when the job coordinates are at a dug out level, but the tiles leading to it are not dug out for the right", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			const sf::Vector2i Coordinates{ 5,1 };

			bool isTileDugOutInvoked = false;
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };
			terrainAlterationService.isTileDugOutCallback = [&](int _level, int _column) {
				REQUIRE(Coordinates.y == _level);
				REQUIRE(1 == _column);
				isTileDugOutInvoked = true;
				return false;
			};

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;
			job.coordinates = Coordinates;

			REQUIRE_FALSE(service.canWorkerAccessJob(worker, job));
			REQUIRE(isTileDugOutInvoked);
		}

		TEST_CASE("canWorkerAccessJob returns false when the job coordinates are at a dug out level, but the tiles leading to it are partially dug out for the right", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			const sf::Vector2i Coordinates{ 5,1 };

			int currentCoordinate = 1;

			int isTileDugOutInvokedCount = 0;
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };
			terrainAlterationService.isTileDugOutCallback = [&](int _level, int _column) {
				REQUIRE(Coordinates.y == _level);
				REQUIRE(currentCoordinate == _column);

				bool result = _column != Coordinates.x - 1;
				currentCoordinate++;
				isTileDugOutInvokedCount++;

				return result;
			};

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;
			job.coordinates = Coordinates;

			REQUIRE_FALSE(service.canWorkerAccessJob(worker, job));
			REQUIRE(Coordinates.x - 1 == isTileDugOutInvokedCount);
		}

		TEST_CASE("canWorkerAccessJob returns true when the job coordinates are at a dug out level, and the tiles leading to it are dug out for the right", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			const sf::Vector2i Coordinates{ 5,1 };

			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };
			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;
			job.coordinates = Coordinates;

			REQUIRE(service.canWorkerAccessJob(worker, job));
		}
			   
		TEST_CASE("canWorkerAccessJob returns false when the job coordinates are at a dug out level, but the tiles leading to it are not dug out for the left", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			const sf::Vector2i Coordinates{ -5,1 };

			bool isTileDugOutInvoked = false;
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };
			terrainAlterationService.isTileDugOutCallback = [&](int _level, int _column) {
				REQUIRE(Coordinates.y == _level);
				REQUIRE(-1 == _column);
				isTileDugOutInvoked = true;
				return false;
			};

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;
			job.coordinates = Coordinates;

			REQUIRE_FALSE(service.canWorkerAccessJob(worker, job));
			REQUIRE(isTileDugOutInvoked);
		}

		TEST_CASE("canWorkerAccessJob returns false when the job coordinates are at a dug out level, but the tiles leading to it are partially dug out for the left", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			const sf::Vector2i Coordinates{ -5,1 };

			int currentCoordinate = -1;

			int isTileDugOutInvokedCount = 0;
			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };
			terrainAlterationService.isTileDugOutCallback = [&](int _level, int _column) {
				REQUIRE(Coordinates.y == _level);
				REQUIRE(currentCoordinate == _column);

				bool result = _column != Coordinates.x + 1;
				currentCoordinate--;
				isTileDugOutInvokedCount++;

				return result;
			};

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;
			job.coordinates = Coordinates;

			REQUIRE_FALSE(service.canWorkerAccessJob(worker, job));
			REQUIRE(std::abs(Coordinates.x) - 1 == isTileDugOutInvokedCount);
		}

		TEST_CASE("canWorkerAccessJob returns true when the job coordinates are at a dug out level, and the tiles leading to it are dug out for the left", "[Driller][Services][JobAllocationService]") {
			WorkerData workerData{};
			JobData jobData{};
			TerrainAlterationServiceMock terrainAlterationService;
			JobAllocationService service(workerData, jobData, terrainAlterationService);

			const sf::Vector2i Coordinates{ -5,1 };

			terrainAlterationService.doesLevelExistCallback = [](int) { return true; };
			terrainAlterationService.isTileDugOutCallback = [](int, int) { return true; };

			const JobPrototypeId JobId = inf::djb_hash(drl::Definitions::JobPrototypeName_Dig);

			WorkerInstance worker{};
			worker.validJobTypes = { JobId };
			JobInstance job{};
			job.prototypeId = JobId;
			job.coordinates = Coordinates;

			REQUIRE(service.canWorkerAccessJob(worker, job));
		}
	}
}
