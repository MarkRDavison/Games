#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/ShuttleCreationService.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>

namespace drl {
	namespace ShuttleCreationServiceTests {
		
		struct Package {
			
			Package(void) :
				service(data, shuttlePrototype) {
				
			}

			ShuttleData data;
			ShuttlePrototypeServiceMock shuttlePrototype;
			ShuttleCreationService service;

		};

		TEST_CASE("canCreateShuttle returns false when the shuttle prototype service does not have the shuttle registered", "[Driller][Services][ShuttleCreationService]") {
			Package package{};

			GameCommand::CreateShuttleEvent event{};

			bool isPrototypeRegisteredByIdCallbackInvoked = false;
			package.shuttlePrototype.isPrototypeRegisteredByIdCallback = [&](const ShuttlePrototypeId& _id) {
				isPrototypeRegisteredByIdCallbackInvoked = true;
				return false;
			};

			REQUIRE_FALSE(package.service.canCreateShuttle(event));
			REQUIRE(isPrototypeRegisteredByIdCallbackInvoked);
		}

		TEST_CASE("canCreateShuttle returns false when the shuttle prototype already exists as an instance", "[Driller][Services][ShuttleCreationService]") {
			Package package{};

			GameCommand::CreateShuttleEvent event{};
			event.prototypeId = inf::djb_hash(Definitions::ShuttlePrototypeName_Starting);

			package.shuttlePrototype.isPrototypeRegisteredByIdCallback = [](const ShuttlePrototypeId& _id) { return true; };

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.prototypeId = event.prototypeId;

			REQUIRE_FALSE(package.service.canCreateShuttle(event));
		}

		TEST_CASE("canCreateShuttle returns true when the shuttle prototype is registered and doesn't exist as an instance", "[Driller][Services][ShuttleCreationService]") {
			Package package{};

			GameCommand::CreateShuttleEvent event{};
			event.prototypeId = inf::djb_hash(Definitions::ShuttlePrototypeName_Starting);

			package.shuttlePrototype.isPrototypeRegisteredByIdCallback = [](const ShuttlePrototypeId& _id) { return true; };

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.prototypeId = event.prototypeId + 1;
			
			REQUIRE(package.service.canCreateShuttle(event));
		}

		TEST_CASE("createShuttle invokes createInstance on the shuttle prototype service and emplaces a new shuttle", "[Driller][Services][ShuttleCreationService]") {
			Package package{};

			GameCommand::CreateShuttleEvent event{};
			event.prototypeId = inf::djb_hash(Definitions::ShuttlePrototypeName_Starting);

			ShuttleInstance instance{};
			instance.prototypeId = event.prototypeId;

			bool createInstanceByIdCallbackInvoked = false;
			package.shuttlePrototype.createInstanceByIdCallback = [&](const ShuttlePrototypeId & _prototypeId) {
				createInstanceByIdCallbackInvoked = true;
				return instance;
			};

			package.service.createShuttle(event);

			REQUIRE(1 == package.data.shuttles.size());
			REQUIRE(createInstanceByIdCallbackInvoked);
		}
	}
}
