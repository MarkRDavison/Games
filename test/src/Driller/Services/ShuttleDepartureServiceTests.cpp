#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/ShuttleDepartureService.hpp>
#include <Mocks/Driller/Services/ShuttleCreationServiceMock.hpp>

namespace drl {
	namespace ShuttleDepartureServiceTests {

		struct Package {
			Package(void) :
				service(shuttleCreation) {
				
			}
			ShuttleCreationServiceMock shuttleCreation;
			ShuttleDepartureService service;
		};
		
		TEST_CASE("registerShuttle correctly registers the prototype and departure interval", "[Driller][Services][ShuttleDepartureService]") {
			Package package{};

			const ShuttlePrototypeId Id{ 2u };
			const float DepartureInterval{ 5.0f };

			package.service.registerShuttle(Id, DepartureInterval);

			REQUIRE(Id == package.service.getCurrentPrototypeId());
			REQUIRE(DepartureInterval == package.service.getCurrentDepartureInterval());
		}

		TEST_CASE("update less than the departure interval does not trigger a shuttle creation", "[Driller][Services][ShuttleDepartureService]") {
			Package package{};

			const ShuttlePrototypeId Id{ 2u };
			const float DepartureInterval{ 5.0f };

			package.service.registerShuttle(Id, DepartureInterval);

			bool createShuttleInvoked = false;
			package.shuttleCreation.canCreateShuttleCallback = [&](const GameCommand::CreateShuttleEvent _command) -> bool {
				createShuttleInvoked = true;
				return false;
			};

			package.service.update(DepartureInterval - 1.0f);

			REQUIRE_FALSE(createShuttleInvoked);
		}

		TEST_CASE("update equal to the departure interval triggers a shuttle creation", "[Driller][Services][ShuttleDepartureService]") {
			Package package{};

			const ShuttlePrototypeId Id{ 2u };
			const float DepartureInterval{ 5.0f };

			package.service.registerShuttle(Id, DepartureInterval);

			bool createShuttleInvoked = false;
			package.shuttleCreation.canCreateShuttleCallback = [&](const GameCommand::CreateShuttleEvent _command) -> bool {
				createShuttleInvoked = true;
				return false;
			};

			package.service.update(DepartureInterval);

			REQUIRE(createShuttleInvoked);
		}

		TEST_CASE("setting shuttle on run means as much as you update another shuttle is not created", "[Driller][Services][ShuttleDepartureService]") {
			Package package{};

			const ShuttlePrototypeId Id{ 2u };
			const float DepartureInterval{ 5.0f };

			package.service.registerShuttle(Id, DepartureInterval);
			package.service.setShuttleOnRun(true);
			bool createShuttleInvoked = false;
			package.shuttleCreation.canCreateShuttleCallback = [&](const GameCommand::CreateShuttleEvent _command) -> bool {
				createShuttleInvoked = true;
				return false;
			};

			package.service.update(DepartureInterval * 10.0f);

			REQUIRE_FALSE(createShuttleInvoked);
		}

		TEST_CASE("creating a shuttle sets on a run", "[Driller][Services][ShuttleDepartureService]") {
			Package package{};

			const ShuttlePrototypeId Id{ 2u };
			const float DepartureInterval{ 5.0f };


			package.shuttleCreation.canCreateShuttleCallback = [&](const GameCommand::CreateShuttleEvent _command) -> bool { return true; };

			package.service.registerShuttle(Id, DepartureInterval);
			package.service.update(DepartureInterval);

			REQUIRE(package.service.getShuttleOnRun());
		}

		TEST_CASE("addWorkerPrototypeToQueue allows peeking and popping in fifo order when all workers can be created", "[Driller][Services][ShuttleDepartureService]") {
			Package package{};

			const std::size_t Amount = 5u;
			for (int i = 0; i < Amount; ++i) {
				package.service.addWorkerPrototypeToQueue(i);
			}
			for (int i = 0; i < Amount; ++i) {
				REQUIRE_FALSE(package.service.workerPrototypeQueueEmpty(0));
				REQUIRE(i == package.service.peekWorkerPrototypeQueue(0));
				package.service.popWorkerPrototoypeQueue(0);
			}
			REQUIRE(package.service.workerPrototypeQueueEmpty(0));
		}

		TEST_CASE("workerPrototypeQueueEmpty returns correct answers when number of failed peeks increases", "[Driller][Services][ShuttleDepartureService]") {
			Package package{};

			const std::size_t Amount = 5u;
			for (int i = 0; i < Amount; ++i) {
				package.service.addWorkerPrototypeToQueue(i);
			}

			for (int i = 0; i < Amount; ++i) {
				REQUIRE_FALSE(package.service.workerPrototypeQueueEmpty(i));
			}
			REQUIRE(package.service.workerPrototypeQueueEmpty(Amount));
		}

	}
}
