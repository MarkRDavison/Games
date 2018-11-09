#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/WorkerUpdateService.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Mocks/Driller/Services/JobCompletionServiceMock.hpp>
#include <Mocks/Driller/Services/NeedProviderLocationServiceMock.hpp>

namespace drl {
	namespace WorkerUpdateServiceTests {

		struct Package {

			Package(void) :
				service(workerData, buildingData, jobData, jobCompletionService, needProviderLocationService) {
				
			}

			WorkerData workerData{}; 
			BuildingData buildingData{};
			JobData jobData{};
			JobCompletionServiceMock jobCompletionService;
			NeedProviderLocationServiceMock needProviderLocationService;
			WorkerUpdateService service;
		};
		
		TEST_CASE("updating idle worker from idle state with job assigned updates state to working job", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;

			package.service.updateIdleWorker(worker, 1.0f);

			REQUIRE(WorkerInstance::WorkerState::MovingToJob == worker.state);
		}

		TEST_CASE("updating moving to job worker with no allocated job updates state to idle", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = false;
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;

			package.service.updateIdleWorker(worker, 1.0f);

			REQUIRE(WorkerInstance::WorkerState::Idle == worker.state);
		}

		TEST_CASE("updating moving to job worker with no allocated job id updates state to idle", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = 0u;
			worker.hasAllocatedJob = true;
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;

			package.service.updateIdleWorker(worker, 1.0f);

			REQUIRE(WorkerInstance::WorkerState::Idle == worker.state);
		}

		TEST_CASE("populatePath where worker is already at its target does nothing", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const sf::Vector2i Coordinates{ 1,1 };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			worker.position = sf::Vector2f(Coordinates);
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;
			job.coordinates = Coordinates;

			package.service.populatePath(worker, Coordinates, WorkerInstance::WorkerState::WorkingJob);

			REQUIRE_FALSE(worker.path.path.isValid);
			REQUIRE(worker.path.path.nodes.empty());
		}

		TEST_CASE("populatePath where worker is already on same level as target creates path with only start and end nodes", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const sf::Vector2i WorkerCoordinates{ 1,1 };
			const sf::Vector2i JobCoordinates{ 4,1 };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			worker.position = sf::Vector2f(WorkerCoordinates);
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;
			job.coordinates = JobCoordinates;

			package.service.populatePath(worker, JobCoordinates, WorkerInstance::WorkerState::WorkingJob);

			REQUIRE(worker.path.path.isValid);
			REQUIRE(inf::PathNode::NodeType::Start == worker.path.path.nodes[0].nodeType);
			REQUIRE(WorkerCoordinates.x == worker.path.path.nodes[0].x);
			REQUIRE(WorkerCoordinates.y == worker.path.path.nodes[0].y);
			REQUIRE(inf::PathNode::NodeType::End == worker.path.path.nodes[1].nodeType);
			REQUIRE(JobCoordinates.x == worker.path.path.nodes[1].x);
			REQUIRE(JobCoordinates.y == worker.path.path.nodes[1].y);
		}

		TEST_CASE("populatePath where worker is on different level as target creates path with 4 nodes", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const sf::Vector2i WorkerCoordinates{ 1,1 };
			const sf::Vector2i JobCoordinates{ 4,3 };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = { 1u };
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = { 2u };

			worker.allocatedJobId = job.Id;
			worker.hasAllocatedJob = true;
			worker.position = sf::Vector2f(WorkerCoordinates);
			job.allocatedWorkerId = worker.Id;
			job.allocated = true;
			job.coordinates = JobCoordinates;

			package.service.populatePath(worker, JobCoordinates, WorkerInstance::WorkerState::WorkingJob);

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
			Package package{};

			const int Speed = static_cast<int>(Definitions::BaseWorkerMovementSpeed);

			const sf::Vector2i WorkerCoordinates{ 1,1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed,1 };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ NodeCoordinates.x, NodeCoordinates.y, inf::PathNode::NodeType::End });

			package.service.followPath(worker, 0.5f, WorkerInstance::WorkerState::WorkingJob);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(2.0f, 1.0f) == worker.position);
		}

		TEST_CASE("followPath moves to the next node in the path if it can reach it", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const int Speed = static_cast<int>(Definitions::BaseWorkerMovementSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed, 1 };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ NodeCoordinates.x, NodeCoordinates.y, inf::PathNode::NodeType::Standard });
			worker.path.path.nodes.emplace_back(inf::PathNode{ NodeCoordinates.x + 1, NodeCoordinates.y, inf::PathNode::NodeType::End });

			package.service.followPath(worker, 1.0f, WorkerInstance::WorkerState::WorkingJob);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(NodeCoordinates) == worker.position);
		}

		TEST_CASE("followPath moves past a node if it has enough speed", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const int Speed = static_cast<int>(Definitions::BaseWorkerMovementSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed * 2, 1 };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 1, WorkerCoordinates.y, inf::PathNode::NodeType::Standard });
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 3, WorkerCoordinates.y, inf::PathNode::NodeType::End });

			package.service.followPath(worker, 2.0f, WorkerInstance::WorkerState::WorkingJob);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(NodeCoordinates) == worker.position);
		}

		TEST_CASE("followPath moves past a node if it has enough speed and can go in different directions", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const int Speed = static_cast<int>(Definitions::BaseWorkerMovementSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };
			const sf::Vector2i NodeCoordinates{ 1 + Speed, 1 + Speed };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 1, WorkerCoordinates.y, inf::PathNode::NodeType::Standard });
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed * 1, WorkerCoordinates.y + Speed * 2, inf::PathNode::NodeType::End });

			package.service.followPath(worker, 2.0f, WorkerInstance::WorkerState::WorkingJob);

			REQUIRE(1u == worker.path.path.nodes.size());
			REQUIRE(sf::Vector2f(NodeCoordinates) == worker.position);
		}


		TEST_CASE("followPath sets the path back to invalid when the path is complete, and the workers state is updated", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const int Speed = static_cast<int>(Definitions::BaseWorkerMovementSpeed);

			const sf::Vector2i WorkerCoordinates{ 1, 1 };

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.position = sf::Vector2f(WorkerCoordinates);
			worker.path.path.nodes.emplace_back(inf::PathNode{ WorkerCoordinates.x + Speed, WorkerCoordinates.y, inf::PathNode::NodeType::End });

			package.service.followPath(worker, 1.0f, WorkerInstance::WorkerState::WorkingJob);

			REQUIRE_FALSE(worker.path.path.isValid);
			REQUIRE(WorkerInstance::WorkerState::WorkingJob == worker.state);
		}

		TEST_CASE("updateWorkingJobWorker updates worked time on job", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = worker.allocatedJobId;

			package.service.updateWorkingJobWorker(worker, 1.0f);

			REQUIRE(1.0f == job.workPerformed);
		}

		TEST_CASE("updateWorkingJobWorker where the job gets completed invokes the job completion service", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = worker.allocatedJobId;
			job.workRequired = 1.0f;

			bool jobCompletionInvoked = false;
			package.jobCompletionService.defaultJobCompleteDelegate = [&](const JobInstance& _jobInstance) {
				REQUIRE(job.Id == _jobInstance.Id);
				jobCompletionInvoked = true;
			};

			package.jobCompletionService.isJobCompleteDelegateRegisteredCallback = [](const JobPrototypeId&) {
				return true;
			};

			package.service.updateWorkingJobWorker(worker, job.workRequired);
			
			REQUIRE(jobCompletionInvoked);
		}

		TEST_CASE("updateWorkingJobWorker where the job gets completed handles the job complete before invoking the job complete delegate", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			JobInstance& job = package.jobData.jobs.emplace_back();
			job.Id = worker.allocatedJobId;
			job.workRequired = 1.0f;

			bool jobCompletionInvoked = false;
			bool handleJobCompleteInvoked = false;
			package.jobCompletionService.defaultJobCompleteDelegate = [&](const JobInstance& _jobInstance) {
				REQUIRE(handleJobCompleteInvoked);
				REQUIRE(job.Id == _jobInstance.Id);
				jobCompletionInvoked = true;
			};
			package.jobCompletionService.handleJobCompletedCallback = [&](JobInstance& _job) -> void {
				REQUIRE_FALSE(handleJobCompleteInvoked);
				handleJobCompleteInvoked = true;
			};
			package.jobCompletionService.isJobCompleteDelegateRegisteredCallback = [](const JobPrototypeId&) -> bool { return true; };

			package.service.updateWorkingJobWorker(worker, job.workRequired);

			REQUIRE(jobCompletionInvoked);
			REQUIRE(handleJobCompleteInvoked);
		}

		TEST_CASE("updateWorkerNeeds reduces time on worker needs", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const NeedInstance needs;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			worker.needs = needs;

			package.service.updateWorkerNeeds(worker, Delta);

			REQUIRE(needs.fun - Delta == worker.needs.fun);
			REQUIRE(needs.nutrition - Delta == worker.needs.nutrition);
			REQUIRE(needs.sleep - Delta == worker.needs.sleep);
		}

		TEST_CASE("updateWorkerNeeds where one is reduced entirely keeps current state if need provider cannot be found for nutrition", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const NeedInstance needs;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			worker.needs = needs;
			worker.needs.fun = 1000.0f;
			worker.needs.sleep = 1000.0f;

			package.needProviderLocationService.isNeedProviderAvailableCallback.registerCallback([](std::size_t _needId) -> bool {
				REQUIRE(inf::djb_hash(Definitions::NeedCategory_Nutrition) == _needId);
				return false;
			});

			package.service.updateWorkerNeeds(worker, needs.nutrition - needs.nutritionMinimum);

			REQUIRE(package.needProviderLocationService.isNeedProviderAvailableCallback.isInvokedOnce());
		}

		TEST_CASE("updateWorkerNeeds where one is reduced entirely keeps current state if need provider cannot be found for sleep", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const NeedInstance needs;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			worker.needs = needs;
			worker.needs.fun = 1000.0f;
			worker.needs.nutrition = 1000.0f;

			package.needProviderLocationService.isNeedProviderAvailableCallback.registerCallback([](std::size_t _needId) -> bool {
				REQUIRE(inf::djb_hash(Definitions::NeedCategory_Sleep) == _needId);
				return false;
			});

			package.service.updateWorkerNeeds(worker, needs.sleep - needs.sleepMinimum);

			REQUIRE(package.needProviderLocationService.isNeedProviderAvailableCallback.isInvokedOnce());
		}

		TEST_CASE("updateWorkerNeeds where one is reduced entirely keeps current state if need provider cannot be found for fun", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const NeedInstance needs;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			worker.needs = needs;
			worker.needs.sleep = 1000.0f;
			worker.needs.nutrition = 1000.0f;

			package.needProviderLocationService.isNeedProviderAvailableCallback.registerCallback([](std::size_t _needId) -> bool {
				REQUIRE(inf::djb_hash(Definitions::NeedCategory_Fun) == _needId);
				return false;
			});

			package.service.updateWorkerNeeds(worker, needs.fun - needs.funMinimum);

			REQUIRE(package.needProviderLocationService.isNeedProviderAvailableCallback.isInvokedOnce());
		}

		TEST_CASE("updateWorkerNeeds where one is reduced entirely asks need provider location service to get the need provider", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const NeedInstance needs;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.allocatedJobId = 1u;
			worker.needs = needs;
			worker.needs.sleep = 1000.0f;
			worker.needs.nutrition = 1000.0f;
			worker.position = { 1.0f, 2.0f };

			package.needProviderLocationService.isNeedProviderAvailableCallback.registerCallback([](std::size_t _needId) -> bool { return true; });
			package.needProviderLocationService.getNeedProviderCallback.registerCallback([&](std::size_t _needId, const sf::Vector2f& _position) -> EntityId {
				REQUIRE(inf::djb_hash(Definitions::NeedCategory_Fun) == _needId);
				REQUIRE(worker.position == _position);
				return 0u; 
			});

			package.service.updateWorkerNeeds(worker, needs.fun - needs.funMinimum);

			REQUIRE(package.needProviderLocationService.getNeedProviderCallback.isInvokedOnce());
		}

		TEST_CASE("sendTowardsNeedProvider creates a path towards the need", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = 512u;
			worker.allocatedJobId = 1u;
			worker.position = { 1.0f, 2.0f };
			const EntityId providingNeedId = 55u;

			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.Id = providingNeedId;
			const BuildingProvidedNeed& providedNeed = building.providedNeeds.emplace_back();

			package.service.sendTowardsNeedProvider(worker, providingNeedId);

			REQUIRE(worker.path.path.isValid);
			REQUIRE(worker.Id == providedNeed.allocatedWorkerId);
		}

		TEST_CASE("updateRestoringNeedWorker restores the workers needs", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const float delta = 0.1f;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = 522u;
			worker.needs.fun = 0.0f;
			worker.restoringNeedProviderId = 55u;
			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.providedNeedRate = 60.0f;
			building.Id = worker.restoringNeedProviderId;
			BuildingProvidedNeed& providedNeed = building.providedNeeds.emplace_back();
			building.providedNeedId = inf::djb_hash(Definitions::NeedCategory_Fun);
			providedNeed.allocatedWorkerId = worker.Id;

			package.service.updateRestoringNeedWorker(worker, delta);

			REQUIRE(delta * building.providedNeedRate == worker.needs.fun);
		}

		TEST_CASE("updateRestoringNeedWorker restores the workers to their maximum", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const float delta = 1000.0f;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.Id = 522u;
			worker.needs.fun = 0.0f;
			worker.restoringNeedProviderId = 55u;
			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.providedNeedRate = 60.0f;
			building.Id = worker.restoringNeedProviderId;
			BuildingProvidedNeed& providedNeed = building.providedNeeds.emplace_back();
			building.providedNeedId = inf::djb_hash(Definitions::NeedCategory_Fun);
			providedNeed.allocatedWorkerId = worker.Id;

			package.service.updateRestoringNeedWorker(worker, delta);

			REQUIRE(Definitions::BaseNeedMax_Fun == worker.needs.fun);
		}

		TEST_CASE("updateRestoringNeedWorker changes state to idle once need is restored", "[Driller][Services][WorkerUpdateService]") {
			Package package{};

			const float delta = 1000.0f;
			WorkerInstance& worker = package.workerData.workers.emplace_back();
			worker.state = WorkerInstance::WorkerState::RestoringNeed;
			worker.Id = 522u;
			worker.needs.fun = 0.0f;
			worker.restoringNeedProviderId = 55u;
			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.providedNeedRate = 60.0f;
			building.Id = worker.restoringNeedProviderId;
			BuildingProvidedNeed& providedNeed = building.providedNeeds.emplace_back();
			building.providedNeedId = inf::djb_hash(Definitions::NeedCategory_Fun);
			providedNeed.allocatedWorkerId = worker.Id;

			package.service.updateRestoringNeedWorker(worker, delta);

			REQUIRE(WorkerInstance::WorkerState::Idle == worker.state);
		}
	}
}
