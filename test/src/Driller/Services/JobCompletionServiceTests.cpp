#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/JobCompletionService.hpp>

namespace drl {
	namespace JobCompletionServiceTests {
		
		TEST_CASE("handleJobCompleted marks the job to be removed", "[Driller][Services][JobCompletionService]") {
			JobData jobData{};
			JobCompletionService service(jobData);

			JobInstance job{};

			service.handleJobCompleted(job);

			REQUIRE(job.removalRequired);
		}

		TEST_CASE("registerJobCompleteDelegate returns the same delegate when asked", "[Driller][Services][JobCompletionService]") {
			bool delegateInvoked = false;
			JobCompleteDelegate jobCompleteDelegate = [&](const JobInstance& _instance) {
				delegateInvoked = true;
			};

			const JobPrototypeId Id{ 1u };

			JobData jobData{};
			JobCompletionService service(jobData);

			service.registerJobCompleteDelegate(Id, jobCompleteDelegate);

			REQUIRE(service.isJobCompleteDelegateRegistered(Id));

			JobCompleteDelegate& del = service.getJobCompleteDelegate(Id);

			del({});

			REQUIRE(delegateInvoked);
		}

		TEST_CASE("cleanupCompletedJobs only removes jobs that require removal", "[Driller][Services][JobCompletionService]") {
			JobData jobData{};
			JobCompletionService service(jobData);

			jobData.jobs.emplace_back();
			jobData.jobs.emplace_back();

			service.handleJobCompleted(jobData.jobs.front());
			service.cleanupCompletedJobs();

			REQUIRE(1 == jobData.jobs.size());
		}
	}
}