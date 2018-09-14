#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Services/LevelResourceService.hpp>

namespace itr {
	namespace LevelResourceServiceTests {

		TEST_CASE("Requesting the value of a new resource returns 0", "[Intrusion][Service][LevelResourceService]") {
			LevelResourceService service{};

			REQUIRE(0 == service.getResource(Definitions::LivesResourceName));
		}

		TEST_CASE("Setting a value of a new resource then requesting it returns the expected value", "[Intrusion][Service][LevelResourceService]") {
			const int ResourceValue = 12;

			LevelResourceService service{};
			service.setResource(Definitions::LivesResourceName, ResourceValue);

			REQUIRE(ResourceValue == service.getResource(Definitions::LivesResourceName));
		}

		TEST_CASE("Updating a new resources value sets it to the expected value", "[Intrusion][Service][LevelResourceService]") {
			const int ResourceValue = 12;

			LevelResourceService service{};
			service.updateResource(Definitions::LivesResourceName, ResourceValue);

			REQUIRE(ResourceValue == service.getResource(Definitions::LivesResourceName));
		}

		TEST_CASE("Updating an existing resource increases its value by the expected amount", "[Intrusion][Service][LevelResourceService]") {
			const int StartResourceValue = 12;
			const int UpdateResourceValue = 78;

			LevelResourceService service{};
			service.setResource(Definitions::LivesResourceName, StartResourceValue);
			service.updateResource(Definitions::LivesResourceName, UpdateResourceValue);

			REQUIRE(StartResourceValue + UpdateResourceValue == service.getResource(Definitions::LivesResourceName));
		}

		TEST_CASE("Setting a value of a new resource cant set it past the max once set", "[Intrusion][Service][LevelResourceService]") {
			const int ResourceValue = 78;
			const int MaxResourceValue = 12;

			LevelResourceService service{};
			service.setResourceMaximum(Definitions::LivesResourceName, MaxResourceValue);

			service.setResource(Definitions::LivesResourceName, ResourceValue);

			REQUIRE(ResourceValue > MaxResourceValue);
			REQUIRE(MaxResourceValue == service.getResource(Definitions::LivesResourceName));
		}

		TEST_CASE("Updating a value of an existing resource cant set it past the max once set", "[Intrusion][Service][LevelResourceService]") {
			const int StartResourceValue = 12;
			const int UpdateResourceValue = 96;
			const int MaxResourceValue = 78;

			LevelResourceService service{};
			service.setResourceMaximum(Definitions::LivesResourceName, MaxResourceValue);
			service.setResource(Definitions::LivesResourceName, StartResourceValue);
			service.updateResource(Definitions::LivesResourceName, UpdateResourceValue);

			REQUIRE(StartResourceValue + UpdateResourceValue > MaxResourceValue);
			REQUIRE(MaxResourceValue == service.getResource(Definitions::LivesResourceName));
		}

		TEST_CASE("Setting the value of a new resource notifies its value has been changed", "[Intrusion][Service][LevelResourceService]") {
			const std::string ResourceName = Definitions::LivesResourceName;
			bool resourceChangedInvoked{ false };
			LevelResourceService service{};
			service.resourceChanged = [&](const std::string& _resourceName) {
				resourceChangedInvoked = true;
				REQUIRE(ResourceName == _resourceName);
			};

			service.setResource(ResourceName, 10);

			REQUIRE(resourceChangedInvoked);
		}

		TEST_CASE("Setting the value of an existing resource notifies its value has been changed", "[Intrusion][Service][LevelResourceService]") {
			bool resourceChangedInvoked{ false };
			const std::string ResourceName = Definitions::LivesResourceName;
			LevelResourceService service{};
			service.resourceChanged = [&](const std::string& _resourceName) {
				resourceChangedInvoked = true;
				REQUIRE(ResourceName == _resourceName);
			};
			service.updateResource(ResourceName, 10);

			REQUIRE(resourceChangedInvoked);
		}

		TEST_CASE("empty resource service can afford empty resource bundle", "[Intrusion][Service][LevelResourceService]") {
			LevelResourceService service{};

			REQUIRE(service.canAfford(ResourceBundle()));
		}

		TEST_CASE("empty resource service can afford resource bundle with resources of zero amount", "[Intrusion][Service][LevelResourceService]") {
			LevelResourceService service{};

			ResourceBundle bundle{};
			ResourceBundle::Resource resource{};
			resource.name = Definitions::GoldResourceName;
			resource.amount = 0;
			bundle.resources.push_back(resource);

			REQUIRE(service.canAfford(bundle));
		}

		TEST_CASE("empty resource service cannot afford resource bundle with a single resource with > 0 amount", "[Intrusion][Service][LevelResourceService]") {
			LevelResourceService service{};

			ResourceBundle bundle{};
			ResourceBundle::Resource resource{};
			resource.name = Definitions::GoldResourceName;
			resource.amount = 1;
			bundle.resources.push_back(resource);

			REQUIRE_FALSE(service.canAfford(bundle));
		}

		TEST_CASE("resource service with single resource of large amount can afford resource bundle with a single resource with > 0 amount", "[Intrusion][Service][LevelResourceService]") {
			LevelResourceService service{};

			service.setResource(Definitions::GoldResourceName, 50);

			ResourceBundle bundle{};
			ResourceBundle::Resource resource{};
			resource.name = Definitions::GoldResourceName;
			resource.amount = 1;
			bundle.resources.push_back(resource);

			REQUIRE(service.canAfford(bundle));
		}

		TEST_CASE("resource service with single resource of large amount cannot afford resource bundle with multiple resource with > 0 amount", "[Intrusion][Service][LevelResourceService]") {
			LevelResourceService service{};

			const std::string Gold2ResourceName = "Gold2";
			service.setResource(Definitions::GoldResourceName, 50);

			ResourceBundle bundle{};
			{
				ResourceBundle::Resource resource{};
				resource.name = Definitions::GoldResourceName;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}
			{
				ResourceBundle::Resource resource{};
				resource.name = Gold2ResourceName;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}

			REQUIRE_FALSE(service.canAfford(bundle));
		}

		TEST_CASE("resource service with multiple resource of large amount can afford resource bundle with multiple resource with > 0 amount", "[Intrusion][Service][LevelResourceService]") {
			LevelResourceService service{};

			const std::string Gold2ResourceName = "Gold2";
			service.setResource(Definitions::GoldResourceName, 50);
			service.setResource(Gold2ResourceName, 50);

			ResourceBundle bundle{};
			{
				ResourceBundle::Resource resource{};
				resource.name = Definitions::GoldResourceName;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}
			{
				ResourceBundle::Resource resource{};
				resource.name = Gold2ResourceName;
				resource.amount = 1;
				bundle.resources.push_back(resource);
			}

			REQUIRE(service.canAfford(bundle));
		}
	}
}
