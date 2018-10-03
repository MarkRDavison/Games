#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/WorkerCreationService.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>
#include <Driller/DataStructures/WorkerData.hpp>

namespace drl {
	namespace WorkerCreationServiceTests {

		TEST_CASE("canCreateWorker returns false when the prototype is not registered", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerCreationService service(workerData, workerPrototypeService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_All, {} };

			bool isPrototypeRegisteredInvoked = false;
			workerPrototypeService.isPrototypeRegisteredByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				REQUIRE(event.prototypeId == _id);
				isPrototypeRegisteredInvoked = true;
				return false;
			};

			REQUIRE_FALSE(service.canCreateWorker(event));
			REQUIRE(isPrototypeRegisteredInvoked);
		}

		TEST_CASE("canCreateWorker returns true when the prototype is registered", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerCreationService service(workerData, workerPrototypeService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_All, {} };

			bool isPrototypeRegisteredInvoked = false;
			workerPrototypeService.isPrototypeRegisteredByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				REQUIRE(event.prototypeId == _id);
				isPrototypeRegisteredInvoked = true;
				return true;
			};

			REQUIRE(service.canCreateWorker(event));
			REQUIRE(isPrototypeRegisteredInvoked);
		}

		TEST_CASE("createWorker creates an instance", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerCreationService service(workerData, workerPrototypeService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_All, {} };
			drl::WorkerInstance prototype{};

			bool createInstanceInvoked = false;
			workerPrototypeService.createInstanceByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				REQUIRE(event.prototypeId == _id);
				createInstanceInvoked = true;
				return prototype;
			};

			service.createWorker(event);

			REQUIRE(createInstanceInvoked);
		}

		TEST_CASE("createWorker adds a new worker instance", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerCreationService service(workerData, workerPrototypeService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_All, {} };
			drl::WorkerInstance instance{};

			workerPrototypeService.createInstanceByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				return instance;
			};

			service.createWorker(event);

			REQUIRE(1 == workerData.workers.size());
		}

		TEST_CASE("createWorker adds a new worker instance with the correct position", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerCreationService service(workerData, workerPrototypeService);

			const sf::Vector2f Position{ 1.0f, 2.0f };
			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_All, Position };
			drl::WorkerInstance instance{};

			workerPrototypeService.createInstanceByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				return instance;
			};

			service.createWorker(event);

			const WorkerInstance& worker = workerData.workers[0];

			REQUIRE(Position == worker.position);
		}

	}
}
