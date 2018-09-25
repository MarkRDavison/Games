#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Infrastructure/Services/ResourceService.hpp>

#define RESOURCE_1 "Lives"
#define RESOURCE_2 "Gold"
#define RESOURCE_3 "Deaths"

namespace inf {
	namespace ResourceServiceTests {

		TEST_CASE("Requesting the value of a new resource returns 0", "[Intrusion][Service][ResourceService]") {
			ResourceService service{};

			REQUIRE(0 == service.getResource(RESOURCE_1));
		}

		TEST_CASE("Setting a value of a new resource then requesting it returns the expected value", "[Intrusion][Service][ResourceService]") {
			const int ResourceValue = 12;

			ResourceService service{};
			service.setResource(RESOURCE_1, ResourceValue);

			REQUIRE(ResourceValue == service.getResource(RESOURCE_1));
		}

		TEST_CASE("Updating a new resources value sets it to the expected value", "[Intrusion][Service][ResourceService]") {
			const int ResourceValue = 12;

			ResourceService service{};
			service.updateResource(RESOURCE_1, ResourceValue);

			REQUIRE(ResourceValue == service.getResource(RESOURCE_1));
		}

		TEST_CASE("Updating an existing resource increases its value by the expected amount", "[Intrusion][Service][ResourceService]") {
			const int StartResourceValue = 12;
			const int UpdateResourceValue = 78;

			ResourceService service{};
			service.setResource(RESOURCE_1, StartResourceValue);
			service.updateResource(RESOURCE_1, UpdateResourceValue);

			REQUIRE(StartResourceValue + UpdateResourceValue == service.getResource(RESOURCE_1));
		}

		TEST_CASE("Setting a value of a new resource cant set it past the max once set", "[Intrusion][Service][ResourceService]") {
			const int ResourceValue = 78;
			const int MaxResourceValue = 12;

			ResourceService service{};
			service.setResourceMaximum(RESOURCE_1, MaxResourceValue);

			service.setResource(RESOURCE_1, ResourceValue);

			REQUIRE(ResourceValue > MaxResourceValue);
			REQUIRE(MaxResourceValue == service.getResource(RESOURCE_1));
		}

		TEST_CASE("Updating a value of an existing resource cant set it past the max once set", "[Intrusion][Service][ResourceService]") {
			const int StartResourceValue = 12;
			const int UpdateResourceValue = 96;
			const int MaxResourceValue = 78;

			ResourceService service{};
			service.setResourceMaximum(RESOURCE_1, MaxResourceValue);
			service.setResource(RESOURCE_1, StartResourceValue);
			service.updateResource(RESOURCE_1, UpdateResourceValue);

			REQUIRE(StartResourceValue + UpdateResourceValue > MaxResourceValue);
			REQUIRE(MaxResourceValue == service.getResource(RESOURCE_1));
		}

		TEST_CASE("Setting the value of a new resource notifies its value has been changed", "[Intrusion][Service][ResourceService]") {
			const std::string ResourceName = RESOURCE_1;
			bool resourceChangedInvoked{ false };
			ResourceService service{};
			service.resourceChanged.registerCallback([&](const std::string& _resourceName) {
				resourceChangedInvoked = true;
				REQUIRE(ResourceName == _resourceName);
			});

			service.setResource(ResourceName, 10);

			REQUIRE(resourceChangedInvoked);
		}

		TEST_CASE("Setting the value of an existing resource notifies its value has been changed", "[Intrusion][Service][ResourceService]") {
			bool resourceChangedInvoked{ false };
			const std::string ResourceName = RESOURCE_1;
			ResourceService service{};
			service.resourceChanged.registerCallback([&](const std::string& _resourceName) {
				resourceChangedInvoked = true;
				REQUIRE(ResourceName == _resourceName);
			});
			service.updateResource(ResourceName, 10);

			REQUIRE(resourceChangedInvoked);
		}

		TEST_CASE("empty resource service can afford empty resource bundle", "[Intrusion][Service][ResourceService]") {
			ResourceService service{};

			REQUIRE(service.canAfford(ResourceBundle()));
		}

		TEST_CASE("empty resource service can afford resource bundle with resources of zero amount", "[Intrusion][Service][ResourceService]") {
			ResourceService service{};

			ResourceBundle bundle{};
			ResourceBundle::Resource resource{};
			resource.name = RESOURCE_2;
			resource.amount = 0;
			bundle.resources.push_back(resource);

			REQUIRE(service.canAfford(bundle));
		}

		TEST_CASE("empty resource service cannot afford resource bundle with a single resource with > 0 amount", "[Intrusion][Service][ResourceService]") {
			ResourceService service{};

			ResourceBundle bundle{};
			ResourceBundle::Resource resource{};
			resource.name = RESOURCE_2;
			resource.amount = 1;
			bundle.resources.push_back(resource);

			REQUIRE_FALSE(service.canAfford(bundle));
		}

		TEST_CASE("resource service with single resource of large amount can afford resource bundle with a single resource with > 0 amount", "[Intrusion][Service][ResourceService]") {
			ResourceService service{};

			service.setResource(RESOURCE_2, 50);

			ResourceBundle bundle{};
			ResourceBundle::Resource resource{};
			resource.name = RESOURCE_2;
			resource.amount = 1;
			bundle.resources.push_back(resource);

			REQUIRE(service.canAfford(bundle));
		}

		TEST_CASE("resource service with single resource of large amount cannot afford resource bundle with multiple resource with > 0 amount", "[Intrusion][Service][ResourceService]") {
			ResourceService service{};

			service.setResource(RESOURCE_2, 50);

			ResourceBundle bundle{};
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_2;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_3;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}

			REQUIRE_FALSE(service.canAfford(bundle));
		}

		TEST_CASE("resource service with multiple resource of large amount can afford resource bundle with multiple resource with > 0 amount", "[Intrusion][Service][ResourceService]") {
			ResourceService service{};

			service.setResource(RESOURCE_2, 50);
			service.setResource(RESOURCE_3, 50);

			ResourceBundle bundle{};
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_2;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_3;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}

			REQUIRE(service.canAfford(bundle));
		}

		TEST_CASE("Paying a resource bundle reduces all relevant resources", "[Intrusion][Service][ResourceService]") {
			const int StartingAmount = 50;
			const int Gold1PayAmount = 12;
			const int Gold2PayAmount = 22;
			ResourceService service{};

			service.setResource(RESOURCE_2, StartingAmount);
			service.setResource(RESOURCE_3, StartingAmount);

			ResourceBundle bundle{};
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_2;
				resource.amount = Gold1PayAmount;
				bundle.resources.push_back(resource);
			}
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_3;
				resource.amount = Gold2PayAmount;
				bundle.resources.push_back(resource);
			}

			service.payResourceBundle(bundle);

			REQUIRE(StartingAmount - Gold1PayAmount == service.getResource(RESOURCE_2));
			REQUIRE(StartingAmount - Gold2PayAmount == service.getResource(RESOURCE_3));
		}

		TEST_CASE("Receiving a resource bundle increases all relevant resources", "[Intrusion][Service][ResourceService]") {
			const int StartingAmount = 50;
			const int Gold1PayAmount = 12;
			const int Gold2PayAmount = 22;
			ResourceService service{};

			service.setResource(RESOURCE_2, StartingAmount);
			service.setResource(RESOURCE_3, StartingAmount);

			ResourceBundle bundle{};
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_2;
				resource.amount = Gold1PayAmount;
				bundle.resources.push_back(resource);
			}
			{
				ResourceBundle::Resource resource{};
				resource.name = RESOURCE_3;
				resource.amount = Gold2PayAmount;
				bundle.resources.push_back(resource);
			}

			service.receiveResourceBundle(bundle);

			REQUIRE(StartingAmount + Gold1PayAmount == service.getResource(RESOURCE_2));
			REQUIRE(StartingAmount + Gold2PayAmount == service.getResource(RESOURCE_3));
		}
	}
}
