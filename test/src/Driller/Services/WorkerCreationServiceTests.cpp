#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/WorkerCreationService.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>
#include <Driller/DataStructures/WorkerData.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>
#include <Mocks/Driller/Services/WorkerClassServiceMock.hpp>

namespace drl {
	namespace WorkerCreationServiceTests {

		TEST_CASE("canCreateWorker returns false when the prototype is not registered", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, {} };

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
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, {} };

			bool isPrototypeRegisteredInvoked = false;
			workerPrototypeService.isPrototypeRegisteredByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				REQUIRE(event.prototypeId == _id);
				isPrototypeRegisteredInvoked = true;
				return true;
			};

			workerClassService.canIncreaseClassCallback = [](const WorkerPrototypeId&, int) { return true; };

			REQUIRE(service.canCreateWorker(event));
			REQUIRE(isPrototypeRegisteredInvoked);
		}

		TEST_CASE("createWorker creates an instance", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, {} };
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
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, {} };
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
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const sf::Vector2f Position{ 1.0f, 2.0f };
			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, Position };
			drl::WorkerInstance instance{};

			workerPrototypeService.createInstanceByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				return instance;
			};

			service.createWorker(event);

			const WorkerInstance& worker = workerData.workers[0];

			REQUIRE(Position == worker.position);
		}

		TEST_CASE("create worker increases the worker resource count", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, {} };
			drl::WorkerInstance instance{};

			bool increaseClassCallbackInvoked = false;
			workerClassService.increaseClassCallback = [&](const WorkerPrototypeId& _prototypeId, int _amount) {
				increaseClassCallbackInvoked = true;
				REQUIRE(event.prototypeId == _prototypeId);
				REQUIRE(1 == _amount);
			};
			workerPrototypeService.createInstanceByIdCallback = [&](const drl::WorkerPrototypeId& _id) {
				return instance;
			};

			service.createWorker(event);

			REQUIRE(increaseClassCallbackInvoked);
		}

		TEST_CASE("can create worker returns false when max worker count reached", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, {} };

			bool canIncreaseClassCallbackInvoked = false;

			workerPrototypeService.isPrototypeRegisteredByIdCallback = [](const WorkerPrototypeId&) { return true; };
			workerClassService.canIncreaseClassCallback = [&](const WorkerPrototypeId&, int) {
				canIncreaseClassCallbackInvoked = true;
				return false;
			};

			REQUIRE_FALSE(service.canCreateWorker(event));
			REQUIRE(canIncreaseClassCallbackInvoked);
		}

		TEST_CASE("can create worker returns true when max worker count not reached", "[Driller][Services][WorkerCreationService]") {
			WorkerData workerData{};
			WorkerPrototypeServiceMock workerPrototypeService;
			WorkerClassServiceMock workerClassService;
			WorkerCreationService service(workerData, workerPrototypeService, workerClassService);

			const GameCommand::CreateWorkerEvent event{ Definitions::WorkerPrototypeName_Builder, {} };

			bool canIncreaseClassCallbackInvoked = false;
			workerClassService.canIncreaseClassCallback = [&](const WorkerPrototypeId&, int) {
				canIncreaseClassCallbackInvoked = true;
				return true;
			};
			workerPrototypeService.isPrototypeRegisteredByIdCallback = [](const WorkerPrototypeId&) { return true; };

			REQUIRE(service.canCreateWorker(event));
			REQUIRE(canIncreaseClassCallbackInvoked);
		}

	}
}
