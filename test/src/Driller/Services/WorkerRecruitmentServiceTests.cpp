#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/WorkerRecruitmentService.hpp>
#include <Mocks/Driller/Services/WorkerCreationServiceMock.hpp>
#include <Mocks/Driller/Services/ShuttleDepartureServiceMock.hpp>

namespace drl {
	namespace WorkerRecruitmentServiceTests {
		
		struct Package {
			
			Package(void) :
				service(workerCreation, shuttleDeparture) {
				
			}

			WorkerCreationServiceMock workerCreation;
			ShuttleDepartureServiceMock shuttleDeparture;
			WorkerRecruitmentService service;

		};

		TEST_CASE("recruitWorkers asks the shuttle departure system whether there are any workers queued to be dropped off", "[Driller][Services][WorkerRecruitmentService]") {
			Package package{};

			const int MaxWorkers = 1;
			ShuttleInstance instance{};
			instance.capacity = MaxWorkers;
			WorkerPrototypeId Id{ 1u };

			bool workerPrototypeQueueEmptyCallbackInvoked = false;
			package.shuttleDeparture.workerPrototypeQueueEmptyCallback = [&](int) -> bool { 
				workerPrototypeQueueEmptyCallbackInvoked = true;
				return true; 
			};

			package.service.recruitWorkers(instance);

			REQUIRE(workerPrototypeQueueEmptyCallbackInvoked);
		}

		TEST_CASE("recruitWorkers peeks at a worker prototype", "[Driller][Services][WorkerRecruitmentService]") {
			Package package{};

			const int MaxWorkers = 1;
			ShuttleInstance instance{};
			instance.capacity = MaxWorkers;
			WorkerPrototypeId Id{ 1u };

			package.shuttleDeparture.workerPrototypeQueueEmptyCallback = [&](int _failedWorkers) -> bool { return _failedWorkers != 0; };
			bool peekWorkerPrototypeQueueCallbackInvoked = false;
			package.shuttleDeparture.peekWorkerPrototypeQueueCallback = [&](int _failedWorkers) -> WorkerPrototypeId {
				peekWorkerPrototypeQueueCallbackInvoked = true;
				return Id;
			};

			package.service.recruitWorkers(instance);

			REQUIRE(peekWorkerPrototypeQueueCallbackInvoked);
		}

		TEST_CASE("recruitWorkers asks if the worker can be created", "[Driller][Services][WorkerRecruitmentService]") {
			Package package{};

			const int MaxWorkers = 1;
			ShuttleInstance instance{};
			instance.capacity = MaxWorkers;
			WorkerPrototypeId Id{ 1u };

			package.shuttleDeparture.workerPrototypeQueueEmptyCallback = [&](int _failedWorkers) -> bool { return _failedWorkers != 0; };
			package.shuttleDeparture.peekWorkerPrototypeQueueCallback = [&](int _failedWorkers) -> WorkerPrototypeId { return Id; };
			package.workerCreation.canCreateWorkerCallback = [&](const GameCommand::CreateWorkerEvent&) -> bool { return false; };

			bool canCreateWorkerCallbackInvoked = false;
			package.workerCreation.canCreateWorkerCallback = [&](const GameCommand::CreateWorkerEvent&) -> bool {
				canCreateWorkerCallbackInvoked = true;
				return false;
			};

			package.service.recruitWorkers(instance);

			REQUIRE(canCreateWorkerCallbackInvoked);
		}

		TEST_CASE("recruitWorkers creates the worker if can create worker returned true", "[Driller][Services][WorkerRecruitmentService]") {
			Package package{};

			const int MaxWorkers = 1;
			ShuttleInstance instance{};
			instance.capacity = MaxWorkers;
			instance.position = { 1.0f, 2.0f };
			WorkerPrototypeId Id{ 1u };

			package.shuttleDeparture.workerPrototypeQueueEmptyCallback = [&](int _failedWorkers) -> bool { return _failedWorkers != 0; };
			package.shuttleDeparture.peekWorkerPrototypeQueueCallback = [&](int _failedWorkers) -> WorkerPrototypeId { return Id; };
			package.workerCreation.canCreateWorkerCallback = [&](const GameCommand::CreateWorkerEvent&) -> bool { return true; };

			bool createWorkerCallbackInvoked = false;
			package.workerCreation.createWorkerCallback = [&](const GameCommand::CreateWorkerEvent& _event) -> void {
				REQUIRE(Id == _event.prototypeId);
				REQUIRE(instance.position == _event.position);
				createWorkerCallbackInvoked = true;
			};

			package.service.recruitWorkers(instance);

			REQUIRE(createWorkerCallbackInvoked);
		}

		TEST_CASE("recruitWorkers does not create the worker if can create worker returned false", "[Driller][Services][WorkerRecruitmentService]") {
			Package package{};

			const int MaxWorkers = 1;
			ShuttleInstance instance{};
			instance.capacity = MaxWorkers;
			WorkerPrototypeId Id{ 1u };

			package.shuttleDeparture.workerPrototypeQueueEmptyCallback = [&](int _failedWorkers) -> bool { return _failedWorkers != 0; };
			package.shuttleDeparture.peekWorkerPrototypeQueueCallback = [&](int _failedWorkers) -> WorkerPrototypeId { return Id; };
			package.workerCreation.canCreateWorkerCallback = [&](const GameCommand::CreateWorkerEvent&) -> bool { return false; };

			bool createWorkerCallbackInvoked = false;
			package.workerCreation.createWorkerCallback = [&](const GameCommand::CreateWorkerEvent& _event) -> void {
				createWorkerCallbackInvoked = true;
			};

			package.service.recruitWorkers(instance);

			REQUIRE_FALSE(createWorkerCallbackInvoked);
		}

		TEST_CASE("recruitWorkers is called as many times as the shuttle has capacity", "[Driller][Services][WorkerRecruitmentService]") {
			Package package{};
			
			const int MaxWorkers = 4;
			const int WorkersInQueue = 4;
			ShuttleInstance instance{};
			instance.capacity = MaxWorkers;
			WorkerPrototypeId Id{ 1u };

			int createWorkerCallbackInvokedCount = 0;
			package.shuttleDeparture.workerPrototypeQueueEmptyCallback = [&](int _failedWorkers) -> bool { return WorkersInQueue <= _failedWorkers; };
			package.shuttleDeparture.peekWorkerPrototypeQueueCallback = [&](int _failedWorkers) -> WorkerPrototypeId { return Id; };
			package.workerCreation.canCreateWorkerCallback = [&](const GameCommand::CreateWorkerEvent&) -> bool { return true; };
			package.workerCreation.createWorkerCallback = [&](const GameCommand::CreateWorkerEvent& _event) -> void {
				createWorkerCallbackInvokedCount++;
			};
			
			package.service.recruitWorkers(instance);

			REQUIRE(MaxWorkers == createWorkerCallbackInvokedCount);
		}

		TEST_CASE("recruitWorkers is called as many times as the shuttle has capacity when every second worker cannot be created", "[Driller][Services][WorkerRecruitmentService]") {
			Package package{};

			const int MaxWorkers = 4;
			const int WorkersInQueue = 8;
			ShuttleInstance instance{};
			instance.capacity = MaxWorkers;
			WorkerPrototypeId Id{ 1u };

			int createWorkerCallbackInvokedCount = 0;
			int canCreateWorkerCallbackInvokedCount = 0;
			package.shuttleDeparture.workerPrototypeQueueEmptyCallback = [&](int _failedWorkers) -> bool { return WorkersInQueue <= _failedWorkers; };
			package.shuttleDeparture.peekWorkerPrototypeQueueCallback = [&](int _failedWorkers) -> WorkerPrototypeId { return Id; };
			package.workerCreation.canCreateWorkerCallback = [&](const GameCommand::CreateWorkerEvent&) -> bool { 
				return canCreateWorkerCallbackInvokedCount++ % 2 == 0;
			};
			package.workerCreation.createWorkerCallback = [&](const GameCommand::CreateWorkerEvent& _event) -> void {
				createWorkerCallbackInvokedCount++;
			};

			package.service.recruitWorkers(instance);

			REQUIRE(MaxWorkers == createWorkerCallbackInvokedCount);
		}
	}
}
