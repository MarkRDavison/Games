#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Pollution/Services/WorldInteractionService.hpp>
#include <Mocks/Infrastructure/InputManagerMock.hpp>
#include <Mocks/Infrastructure/ConfigurationManagerMock.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>

namespace pol {
	namespace WorldInteractionServiceTests {

		TEST_CASE("world with no rotation and having screen relative angle on the intersection count as the lower segment", "[Pollution][Services][WorldInteractionService]") {
			const int WorldSize = 36;
			WorldData data{};
			data.Sides = WorldSize;
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			const float SegmentAngleSize = 360.0f / static_cast<float>(WorldSize);
			for (int i = 0; i < WorldSize; ++i) {
				const float angle = static_cast<float>(i) * SegmentAngleSize;

				REQUIRE(i == service.getWorldSegmentIndexForAngle(data, angle));
			}
		}

		TEST_CASE("world with no rotation and having screen relative angle on the center of the intersection count for the correct segment", "[Pollution][Services][WorldInteractionService]") {
			const int WorldSize = 36;
			WorldData data{};
			data.Sides = WorldSize;
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			const float SegmentAngleSize = 360.0f / static_cast<float>(WorldSize);
			for (int i = 0; i < WorldSize; ++i) {
				const float angle = static_cast<float>(i) * SegmentAngleSize + SegmentAngleSize / 2.0f;

				REQUIRE(i == service.getWorldSegmentIndexForAngle(data, angle));
			}
		}

		TEST_CASE("world with rotation equal to half the segment size and having screen relative angle on the intersection count as the correct segment", "[Pollution][Services][WorldInteractionService]") {
			const int WorldSize = 36;
			WorldData data{};
			data.Sides = WorldSize;
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			const float SegmentAngleSize = 360.0f / static_cast<float>(WorldSize);

			for (int j = 0; j < WorldSize; ++j) {
				data.rotation = SegmentAngleSize * static_cast<float>(j);

				for (int i = 0; i < WorldSize; ++i) {
					const float angle = static_cast<float>(i) * SegmentAngleSize;

					REQUIRE((WorldSize + i - j) % WorldSize == service.getWorldSegmentIndexForAngle(data, angle));
				}
			}
		}

		TEST_CASE("getAngleRelativeToCenterOfScreen returns 0 for to the right of center", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2f MousePosition = sf::Vector2f(+11.0f, 0.0f);
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			REQUIRE(0.0f == service.getAngleRelativeToCenterOfScreen(MousePosition));
		}

		TEST_CASE("getAngleRelativeToCenterOfScreen returns 90 for below center", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2f MousePosition = sf::Vector2f(0.0f, +88.0f);
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			REQUIRE(90.0f == service.getAngleRelativeToCenterOfScreen(MousePosition));
		}

		TEST_CASE("getAngleRelativeToCenterOfScreen returns 180 for to the left of center", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2f MousePosition = sf::Vector2f(-14.0f, 0.0f);
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			REQUIRE(180.0f == service.getAngleRelativeToCenterOfScreen(MousePosition));
		}

		TEST_CASE("getAngleRelativeToCenterOfScreen returns 270 for above center", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2f MousePosition = sf::Vector2f(0.0f, -12.0f);
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			REQUIRE(270.0f == service.getAngleRelativeToCenterOfScreen(MousePosition));
		}

		TEST_CASE("getLengthWithinSnapMargin returns false when within below margin", "[Pollution][Services][WorldInteractionService]") {
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			WorldData data{};
			data.SnapMargin = 0.2f;

			REQUIRE_FALSE(service.getLengthWithinSnapMargin(data, 1.0f - 0.1f - data.SnapMargin));
		}

		TEST_CASE("getLengthWithinSnapMargin returns false when within above margin", "[Pollution][Services][WorldInteractionService]") {
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			WorldData data{};
			data.SnapMargin = 0.2f;

			REQUIRE_FALSE(service.getLengthWithinSnapMargin(data, 1.0f + 0.1f + data.SnapMargin));
		}

		TEST_CASE("getLengthWithinSnapMargin returns true when between margin", "[Pollution][Services][WorldInteractionService]") {
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			WorldData data{};
			data.SnapMargin = 0.2f;

			REQUIRE(service.getLengthWithinSnapMargin(data, 1.0f));
		}

		TEST_CASE("getWorldSegmentForEventCoordinates returns 0 for right and ever so slightly down", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2i Size = { 1280, 720 };
			const sf::Vector2i EventCoordinates = { 1280, 361 };
			inf::InputManagerMock inputManager;
			inputManager.m_GetWindowSizeCallback = [&](void) { return Size; };
			inf::ConfigurationManagerMock configurationManagerMock;
			configurationManagerMock.scale = 1.0f;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			WorldData data{};
			data.Sides = 8;

			REQUIRE(0 == service.getWorldSegmentForEventCoordinates(data, EventCoordinates));
		}

		TEST_CASE("getWorldSegmentForEventCoordinates returns 2 for down and ever so slightly left", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2i Size = { 1280, 720 };
			const sf::Vector2i EventCoordinates = { 639, 720 };
			inf::InputManagerMock inputManager;
			inputManager.m_GetWindowSizeCallback = [&](void) { return Size; };
			inf::ConfigurationManagerMock configurationManagerMock;
			configurationManagerMock.scale = 1.0f;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			WorldData data{};
			data.Sides = 8;

			REQUIRE(2 == service.getWorldSegmentForEventCoordinates(data, EventCoordinates));
		}

		TEST_CASE("getWorldSegmentForEventCoordinates returns 4 for left and ever so slightly up", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2i Size = { 1280, 720 };
			const sf::Vector2i EventCoordinates = { 0, 359 };
			inf::InputManagerMock inputManager;
			inputManager.m_GetWindowSizeCallback = [&](void) { return Size; };
			inf::ConfigurationManagerMock configurationManagerMock;
			configurationManagerMock.scale = 1.0f;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			WorldData data{};
			data.Sides = 8;

			REQUIRE(4 == service.getWorldSegmentForEventCoordinates(data, EventCoordinates));
		}

		TEST_CASE("getWorldSegmentForEventCoordinates returns 6 for up and ever so slightly right", "[Pollution][Services][WorldInteractionService]") {
			const sf::Vector2i Size = { 1280, 720 };
			const sf::Vector2i EventCoordinates = { 641, 0 };
			inf::InputManagerMock inputManager;
			inputManager.m_GetWindowSizeCallback = [&](void) { return Size; };
			inf::ConfigurationManagerMock configurationManagerMock;
			configurationManagerMock.scale = 1.0f;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			WorldData data{};
			data.Sides = 8;

			REQUIRE(6 == service.getWorldSegmentForEventCoordinates(data, EventCoordinates));
		}

		TEST_CASE("canPlacePrototypeatSegmentIndex returns insufficent resources when resources are not present", "[Pollution][Services][WorldInteractionService]") {
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			bool canOffordInvoked = false;
			resourceService.canAffordCallback = [&](const inf::ResourceBundle& _resourceBundle) {
				canOffordInvoked = true;
				return false;
			};

			REQUIRE(Definitions::PlaceBuildingResult::InsufficientResources == service.canPlacePrototypeatSegmentIndex(WorldData(), BuildingData(), 0));

			REQUIRE(canOffordInvoked);
		}

		TEST_CASE("canPlacePrototypeatSegmentIndex returns cannot overwrite when building exists in desired location that is active and equally advanced", "[Pollution][Services][WorldInteractionService]") {
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			const int Age = 3;

			WorldData worldData{};
			worldData.Sides = 1;
			BuildingData& existing = worldData.buildings.emplace_back();
			existing.active = true;
			existing.age = Age;
			BuildingData buildingData{};
			buildingData.age = Age;

			resourceService.canAffordCallback = [](const inf::ResourceBundle& _resourceBundle) { return true; };

			REQUIRE(Definitions::PlaceBuildingResult::CannotOverwrite == service.canPlacePrototypeatSegmentIndex(worldData, buildingData, 0));
		}

		TEST_CASE("canPlacePrototypeatSegmentIndex returns place when building exists in desired location that is active and less advanced", "[Pollution][Services][WorldInteractionService]") {
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			const int Age = 3;

			WorldData worldData{};
			worldData.Sides = 1;
			BuildingData& existing = worldData.buildings.emplace_back();
			existing.active = true;
			existing.age = Age - 1;
			BuildingData buildingData{};
			buildingData.age = Age;

			resourceService.canAffordCallback = [](const inf::ResourceBundle& _resourceBundle) { return true; };

			REQUIRE(Definitions::PlaceBuildingResult::CanPlace == service.canPlacePrototypeatSegmentIndex(worldData, buildingData, 0));
		}

		TEST_CASE("canPlacePrototypeatSegmentIndex returns can place when building does not exist", "[Pollution][Services][WorldInteractionService]") {
			inf::InputManagerMock inputManager;
			inf::ConfigurationManagerMock configurationManagerMock;
			inf::ResourceServiceMock resourceService;
			WorldInteractionService service(inputManager, configurationManagerMock, resourceService);

			const int Age = 3;

			WorldData worldData{};
			worldData.Sides = 1;
			worldData.buildings.emplace_back();
			BuildingData buildingData{};
			buildingData.age = Age;

			resourceService.canAffordCallback = [](const inf::ResourceBundle& _resourceBundle) { return true; };

			REQUIRE(Definitions::PlaceBuildingResult::CanPlace == service.canPlacePrototypeatSegmentIndex(worldData, buildingData, 0));
		}
	}
}
