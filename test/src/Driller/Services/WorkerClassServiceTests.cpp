#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/WorkerClassService.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {
	namespace WorkerClassServiceTests {
		
		TEST_CASE("registering a prototype correctly registers it", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };
			const std::string Resource = Definitions::MoneyResourceName;

			service.registerPrototypeToResourceClass(Id, Resource);

			REQUIRE(service.isPrototypeRegistered(Id));
		}

		TEST_CASE("isPrototypeRegistered returns false when the prototype isnt registered", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };

			REQUIRE_FALSE(service.isPrototypeRegistered(Id));
		}

		TEST_CASE("increaseClassMaximum calls the resource service", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };
			const std::string Resource = Definitions::MoneyResourceName;
			const int Amount = 12;

			bool updateResourceMaxCallbackInvoked = false;
			resourceService.updateResourceMaxCallback = [&](const std::string& _resource, int _amount) {
				REQUIRE(Resource == _resource);
				REQUIRE(Amount == _amount);
				updateResourceMaxCallbackInvoked = true;
			};

			service.registerPrototypeToResourceClass(Id, Resource);
			service.increaseClassMaximum(Id, Amount);

			REQUIRE(updateResourceMaxCallbackInvoked);
		}

		TEST_CASE("increaseClass calls the resource service", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };
			const std::string Resource = Definitions::MoneyResourceName;
			const int Amount = 12;

			bool updateResourceCallbackInvoked = false;
			resourceService.updateResourceCallback = [&](const std::string& _resource, int _amount) {
				REQUIRE(Resource == _resource);
				REQUIRE(Amount == _amount);
				updateResourceCallbackInvoked = true;
			};

			service.registerPrototypeToResourceClass(Id, Resource);
			service.increaseClass(Id, Amount);

			REQUIRE(updateResourceCallbackInvoked);
		}

		TEST_CASE("canIncreaseClass returns false when resource max is met", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };
			const std::string Resource = Definitions::MoneyResourceName;
			const int Amount = 5;

			bool getResourceMaxCallbackInvoked = false;
			resourceService.getResourceMaxCallback = [&](const std::string& _resourceName) {
				REQUIRE(Resource == _resourceName);
				getResourceMaxCallbackInvoked = true;
				return Amount;
			};
			bool getResourceCallbackInvoked = false;
			resourceService.getResourceCallback = [&](const std::string& _resourceName) {
				REQUIRE(Resource == _resourceName);
				getResourceCallbackInvoked = true;
				return Amount;
			};

			service.registerPrototypeToResourceClass(Id, Resource);

			REQUIRE_FALSE(service.canIncreaseClass(Id, 1));

			REQUIRE(getResourceMaxCallbackInvoked);
			REQUIRE(getResourceCallbackInvoked);
		}

		TEST_CASE("canIncreaseClass returns true when resource max is not met", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };
			const std::string Resource = Definitions::MoneyResourceName;
			const int Amount = 5;

			bool getResourceMaxCallbackInvoked = false;
			resourceService.getResourceMaxCallback = [&](const std::string& _resourceName) {
				REQUIRE(Resource == _resourceName);
				getResourceMaxCallbackInvoked = true;
				return Amount;
			};
			bool getResourceCallbackInvoked = false;
			resourceService.getResourceCallback = [&](const std::string& _resourceName) {
				REQUIRE(Resource == _resourceName);
				getResourceCallbackInvoked = true;
				return Amount - 1;
			};

			service.registerPrototypeToResourceClass(Id, Resource);

			REQUIRE(service.canIncreaseClass(Id, 1));

			REQUIRE(getResourceMaxCallbackInvoked);
			REQUIRE(getResourceCallbackInvoked);
		}


		TEST_CASE("decreaseClassMaximum calls the resource service", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };
			const std::string Resource = Definitions::MoneyResourceName;
			const int Amount = 12;

			bool updateResourceMaxCallbackInvoked = false;
			resourceService.updateResourceMaxCallback = [&](const std::string& _resource, int _amount) {
				REQUIRE(Resource == _resource);
				REQUIRE(-Amount == _amount);
				updateResourceMaxCallbackInvoked = true;
			};

			service.registerPrototypeToResourceClass(Id, Resource);
			service.decreaseClassMaximum(Id, Amount);

			REQUIRE(updateResourceMaxCallbackInvoked);
		}

		TEST_CASE("decreaseClass calls the resource service", "[Driller][Services][WorkerClassService]") {
			inf::ResourceServiceMock resourceService;
			WorkerClassService service(resourceService);

			const WorkerPrototypeId Id{ 1u };
			const std::string Resource = Definitions::MoneyResourceName;
			const int Amount = 12;

			bool updateResourceCallbackInvoked = false;
			resourceService.updateResourceCallback = [&](const std::string& _resource, int _amount) {
				REQUIRE(Resource == _resource);
				REQUIRE(-Amount == _amount);
				updateResourceCallbackInvoked = true;
			};

			service.registerPrototypeToResourceClass(Id, Resource);
			service.decreaseClass(Id, Amount);

			REQUIRE(updateResourceCallbackInvoked);
		}
	}
}
