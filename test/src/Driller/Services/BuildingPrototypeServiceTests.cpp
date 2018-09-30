#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/BuildingPrototypeService.hpp>
#include <Mocks/Driller/Services/IdentificationServiceMock.hpp>

namespace drl {
	namespace BuildingPrototypeServiceTests {

		TEST_CASE("registering a prototype by name means it is registered by name and id", "[Driller][Services][BuildingPrototypeService]") {
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);

			const BuildingPrototype prototype{};
			const std::string Name = "Name1";

			service.registerPrototype(Name, prototype);

			REQUIRE(service.isPrototypeRegistered(Name));
			REQUIRE(service.isPrototypeRegistered(service.getPrototypeId(Name)));
		}

		TEST_CASE("registering a prototype by id means it is registered by name and id", "[Driller][Services][BuildingPrototypeService]") {
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);

			const BuildingPrototype prototype{};
			const std::string Name = "Name1";

			service.registerPrototype(service.getPrototypeId(Name), prototype);

			REQUIRE(service.isPrototypeRegistered(Name));
			REQUIRE(service.isPrototypeRegistered(service.getPrototypeId(Name)));
		}

		TEST_CASE("registering a prototype by name can then have it retrieved by name", "[Driller][Services][BuildingPrototypeService]") {
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);

			const BuildingPrototype prototype{{1,2},{3,4}};
			const std::string Name = "Name1";

			service.registerPrototype(Name, prototype);

			const BuildingPrototype& registered = service.getPrototype(Name);

			REQUIRE(prototype.size == registered.size);
			REQUIRE(prototype.textureCoords == registered.textureCoords);
		}

		TEST_CASE("registering a prototype by name can then have it retrieved by id", "[Driller][Services][BuildingPrototypeService]") {
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);

			const BuildingPrototype prototype{ {1,2},{3,4} };
			const std::string Name = "Name1";

			service.registerPrototype(Name, prototype);

			const BuildingPrototype& registered = service.getPrototype(service.getPrototypeId(Name));

			REQUIRE(prototype.size == registered.size);
			REQUIRE(prototype.textureCoords == registered.textureCoords);
		}

		TEST_CASE("registering a prototype by id can then have it retrieved by name", "[Driller][Services][BuildingPrototypeService]") {
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);

			const BuildingPrototype prototype{ {1,2},{3,4} };
			const std::string Name = "Name1";

			service.registerPrototype(service.getPrototypeId(Name), prototype);

			const BuildingPrototype& registered = service.getPrototype(Name);

			REQUIRE(prototype.size == registered.size);
			REQUIRE(prototype.textureCoords == registered.textureCoords);
		}

		TEST_CASE("registering a prototype by id can then have it retrieved by id", "[Driller][Services][BuildingPrototypeService]") {
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);

			const BuildingPrototype prototype{ {1,2},{3,4} };
			const std::string Name = "Name1";

			service.registerPrototype(service.getPrototypeId(Name), prototype);

			const BuildingPrototype& registered = service.getPrototype(service.getPrototypeId(Name));

			REQUIRE(prototype.size == registered.size);
			REQUIRE(prototype.textureCoords == registered.textureCoords);
		}

		TEST_CASE("get prototype when it has not been registered throws expected exception", "[Driller][Services][BuildingPrototypeService]") {
			const std::string Name = "Name1";
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);
			
			REQUIRE_THROWS_AS(service.getPrototype(Name), std::logic_error);
		}

		TEST_CASE("create instance by id creates from prototype as expected", "[Driller][Services][BuildingPrototypeService]") {
			IdentificationServiceMock identificationService;
			BuildingPrototypeService service(identificationService);

			const BuildingPrototype prototype{ {1,2},{3,4} };
			const std::string Name = "Name1";

			service.registerPrototype(Name, prototype);

			const BuildingInstance& instance = service.createInstance(service.getPrototypeId(Name));

			REQUIRE(prototype.size == instance.size);
			REQUIRE(prototype.textureCoords == instance.textureCoords);
		}
		
	}
}
