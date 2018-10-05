#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/JobCompletionService.hpp>
#include <Mocks/Driller/Services/TerrainAlterationServiceMock.hpp>

namespace drl {
	namespace JobCompletionServiceTests {

		struct Package {

			Package(void) :
				service(jobData, terrainAlterationService) {
				
			}

			JobData jobData;
			TerrainAlterationServiceMock terrainAlterationService;
			JobCompletionService service;
		};
		
		TEST_CASE("handleJobCompleted marks the job to be removed", "[Driller][Services][JobCompletionService]") {
			Package package{};

			JobInstance job{};

			package.service.handleJobCompleted(job);

			REQUIRE(job.removalRequired);
		}

		TEST_CASE("handleJobCompleted marks the tiles as no longer having a job reserved", "[Driller][Services][JobCompletionService]") {
			Package package{};

			JobInstance job{};
			job.coordinates = { 1,2 };

			bool reserveJobOnTileCallbackInvoked = false;
			package.terrainAlterationService.reserveJobOnTileCallback = [&](int _level, int _column, bool _jobReserved) -> void {
				REQUIRE(job.coordinates.y == _level);
				REQUIRE(job.coordinates.x == _column);
				REQUIRE_FALSE(_jobReserved);
				reserveJobOnTileCallbackInvoked = true;
			};

			package.service.handleJobCompleted(job);

			REQUIRE(reserveJobOnTileCallbackInvoked);
		}

		TEST_CASE("registerJobCompleteDelegate returns the same delegate when asked", "[Driller][Services][JobCompletionService]") {
			bool delegateInvoked = false;
			JobCompleteDelegate jobCompleteDelegate = [&](const JobInstance& _instance) {
				delegateInvoked = true;
			};

			const JobPrototypeId Id{ 1u };

			Package package{};

			package.service.registerJobCompleteDelegate(Id, jobCompleteDelegate);

			REQUIRE(package.service.isJobCompleteDelegateRegistered(Id));

			JobCompleteDelegate& del = package.service.getJobCompleteDelegate(Id);

			del({});

			REQUIRE(delegateInvoked);
		}

		TEST_CASE("cleanupCompletedJobs only removes jobs that require removal", "[Driller][Services][JobCompletionService]") {
			Package package{};

			package.jobData.jobs.emplace_back();
			package.jobData.jobs.emplace_back();

			package.service.handleJobCompleted(package.jobData.jobs.front());
			package.service.cleanupCompletedJobs();

			REQUIRE(1 == package.jobData.jobs.size());
		}
	}
}
