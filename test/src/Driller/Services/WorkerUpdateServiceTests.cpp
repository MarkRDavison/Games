#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/WorkerUpdateService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Mocks/Driller/Services/JobCompletionServiceMock.hpp>

namespace drl {
	namespace WorkerUpdateServiceTests {
		
		TEST_CASE("updating idle worker from idle state with job assigned updates state to working job", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;

			service.updateIdleWorker(worker, 1.0f);

			REQUIRE(WorkerInstance::WorkerState::MovingToJob == worker.state);
		}

		TEST_CASE("updating moving to job worker with no allocated job updates state to idle", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = false;
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;

			service.updateIdleWorker(worker, 1.0f);

			REQUIRE(WorkerInstance::WorkerState::Idle == worker.state);
		}

		TEST_CASE("updating moving to job worker with no allocated job id updates state to idle", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = 0u;
			worker.hasAllocatedJob = true;
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;

			service.updateIdleWorker(worker, 1.0f);

			REQUIRE(WorkerInstance::WorkerState::Idle == worker.state);
		}

		TEST_CASE("populatePath where worker is already at its target does nothing", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const sf::Vector2i Coordinates{ 1,1 };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			worker.position = sf::Vector2f(Coordinates);
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;
			job.coordinates = Coordinates;

			service.populatePath(worker);

			REQUIRE_FALSE(worker.path.path.isValid);
			REQUIRE(worker.path.path.nodes.empty());
		}

		TEST_CASE("populatePath where worker is already on same level as target creates path with only start and end nodes", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const sf::Vector2i WorkerCoordinates{ 1,1 };
			const sf::Vector2i JobCoordinates{ 4,1 };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			worker.position = sf::Vector2f(WorkerCoordinates);
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;
			job.coordinates = JobCoordinates;

			service.populatePath(worker);

			REQUIRE(worker.path.path.isValid);
			REQUIRE(inf::PathNode::NodeType::Start == worker.path.path.nodes[0].nodeType);
			REQUIRE(WorkerCoordinates.x == worker.path.path.nodes[0].x);
			REQUIRE(WorkerCoordinates.y == worker.path.path.nodes[0].y);
			REQUIRE(inf::PathNode::NodeType::End == worker.path.path.nodes[1].nodeType);
			REQUIRE(JobCoordinates.x == worker.path.path.nodes[1].x);
			REQUIRE(JobCoordinates.y == worker.path.path.nodes[1].y);
		}

		TEST_CASE("populatePath where worker is on different level as target creates path with 4 nodes", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const sf::Vector2i WorkerCoordinates{ 1,1 };
			const sf::Vector2i JobCoordinates{ 4,3 };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			worker.position = sf::Vector2f(WorkerCoordinates);
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;
			job.coordinates = JobCoordinates;

			service.populatePath(worker);

			REQUIRE(worker.path.path.isValid);
			REQUIRE(inf::PathNode::NodeType::Start == worker.path.path.nodes[0].nodeType);
			REQUIRE(WorkerCoordinates.x == worker.path.path.nodes[0].x);
			REQUIRE(WorkerCoordinates.y == worker.path.path.nodes[0].y);

			REQUIRE(inf::PathNode::NodeType::Standard == worker.path.path.nodes[1].nodeType);
			REQUIRE(0 == worker.path.path.nodes[1].x);
			REQUIRE(WorkerCoordinates.y == worker.path.path.nodes[1].y);

			REQUIRE(inf::PathNode::NodeType::Standard == worker.path.path.nodes[2].nodeType);
			REQUIRE(0 == worker.path.path.nodes[2].x);
			REQUIRE(JobCoordinates.y == worker.path.path.nodes[2].y);

			REQUIRE(inf::PathNode::NodeType::End == worker.path.path.nodes[3].nodeType);
			REQUIRE(JobCoordinates.x == worker.path.path.nodes[3].x);
			REQUIRE(JobCoordinates.y == worker.path.path.nodes[3].y);
		}

		TEST_CASE("followPath moves towards the next node in the path if it cant reach it", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const int Speed = static_cast<int>(Definitions::BaseWorkerSpeed);

			const sf::Vector2i WorkerCoordinates{ 1,1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed,1 };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ NodeCoordinates.x, NodeCoordinates.y, inf::PathNode::NodeType::End });

			service.followPath(worker, 0.5f);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(2.0f, 1.0f) == worker.position);
		}

		TEST_CASE("followPath moves to the next node in the path if it can reach it", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const int Speed = static_cast<int>(Definitions::BaseWorkerSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed, 1 };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ NodeCoordinates.x, NodeCoordinates.y, inf::PathNode::NodeType::Standard });
			worker.path.path.nodes.emplace_back(inf::PathNode{ NodeCoordinates.x + 1, NodeCoordinates.y, inf::PathNode::NodeType::End });

			service.followPath(worker, 1.0f);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(NodeCoordinates) == worker.position);
		}

		TEST_CASE("followPath moves past a node if it has enough speed", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const int Speed = static_cast<int>(Definitions::BaseWorkerSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed * 2, 1 };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 1, WorkerCoordinates.y, inf::PathNode::NodeType::Standard });
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 3, WorkerCoordinates.y, inf::PathNode::NodeType::End });

			service.followPath(worker, 2.0f);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(NodeCoordinates) == worker.position);
		}

		TEST_CASE("followPath moves past a node if it has enough speed and can go in different directions", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const int Speed = static_cast<int>(Definitions::BaseWorkerSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed, 1 + Speed };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 1, WorkerCoordinates.y, inf::PathNode::NodeType::Standard });
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 1, WorkerCoordinates.y + Speed * 2, inf::PathNode::NodeType::End });

			service.followPath(worker, 2.0f);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(NodeCoordinates) == worker.position);
		}


		TEST_CASE("followPath sets the path back to invalid when the path is complete, and the workers state is updated", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			const int Speed = static_cast<int>(Definitions::BaseWorkerSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed, WorkerCoordinates.y, inf::PathNode::NodeType::End });

			service.followPath(worker, 1.0f);

			REQUIRE_FALSE(worker.path.path.isValid);
			REQUIRE(WorkerInstance::WorkerState::WorkingJob == worker.state);
		}

		TEST_CASE("updateWorkingJobWorker updates worked time on job", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = worker.allocatedJobId;

			service.updateWorkingJobWorker(worker, 1.0f);

			REQUIRE(1.0f == job.workPerformed);
		}

		TEST_CASE("updateWorkingJobWorker where the job gets completed invokes the job completion service", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = worker.allocatedJobId;
			job.workRequired = 1.0f;

			bool jobCompletionInvoked = false;
			jobCompletionService.defaultJobCompleteDelegate = [&](const JobInstance& _jobInstance) {
				REQUIRE(job.Id == _jobInstance.Id);
				jobCompletionInvoked = true;
			};

			jobCompletionService.isJobCompleteDelegateRegisteredCallback = [](const JobPrototypeId&) {
				return true;
			};

			service.updateWorkingJobWorker(worker, job.workRequired);
			
			REQUIRE(jobCompletionInvoked);
		}

		TEST_CASE("updateWorkingJobWorker where the job gets completed handles the job complete before invoking the job complete delegate", "[Driller][Services][WorkerUpdateService]") {
			WorkerData workerData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateService service(workerData, jobData, jobCompletionService);

			WorkerInstance& worker = workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			JobInstance& job = jobData.jobs.emplace_back();
			job.Id = worker.allocatedJobId;
			job.workRequired = 1.0f;

			bool jobCompletionInvoked = false;
			bool handleJobCompleteInvoked = false;
			jobCompletionService.defaultJobCompleteDelegate = [&](const JobInstance& _jobInstance) {
				REQUIRE(handleJobCompleteInvoked);
				REQUIRE(job.Id == _jobInstance.Id);
				jobCompletionInvoked = true;
			};
			jobCompletionService.handleJobCompletedCallback = [&](JobInstance& _job) -> void {
				REQUIRE_FALSE(handleJobCompleteInvoked);
				handleJobCompleteInvoked = true;
			};
			jobCompletionService.isJobCompleteDelegateRegisteredCallback = [](const JobPrototypeId&) -> bool { return true; };

			service.updateWorkingJobWorker(worker, job.workRequired);

			REQUIRE(jobCompletionInvoked);
			REQUIRE(handleJobCompleteInvoked);
		}
	}
}
