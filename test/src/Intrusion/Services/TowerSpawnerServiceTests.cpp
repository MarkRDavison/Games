#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Services/TowerSpawnerService.hpp>
#include <Mocks/Infrastructure/InputManagerMock.hpp>
#include <Mocks/Intrusion/Infrastructure/IntrusionConfigurationManagerMock.hpp>
#include <Mocks/Infrastructure/LuaManagerMock.hpp>
#include <Mocks/Intrusion/Infrastructure/TowerPlaceableSurfaceServiceMock.hpp>
#include <Mocks/Intrusion/Infrastructure/TowerPlaceableSurfaceMock.hpp>
#include <Mocks/Intrusion/Services/LevelResourceServiceMock.hpp>

namespace itr {
	namespace TowerSpawnerServiceTests {

		TEST_CASE("beginGhostForPrototype correctly sets the prototype", "[Intrusion][Service][TowerSpawnerService]") {
			const std::string TowerName = "TestTowerName";
			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			ParsedTower tower{};
			tower.prototypeName = TowerName;

			service.beginGhostForPrototype(tower);

			REQUIRE(TowerName == service.getGhostPrototype().prototypeName);
		}

		TEST_CASE("beginGhostForPrototype correctly starts showing the ghost", "[Intrusion][Service][TowerSpawnerService]") {
			const std::string TowerName = "TestTowerName";
			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype({});

			REQUIRE(service.getShowingTowerGhost());
		}

		TEST_CASE("beginGhostForPrototype with mouse position in negative sets ghost tile coordinates to -1, -1", "[Intrusion][Service][TowerSpawnerService]") {
			const std::string TowerName = "TestTowerName";
			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};

			input.m_GetMousePositionCallback = []() {return sf::Vector2i(-55, -23); };
			
			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype({});

			REQUIRE(sf::Vector2i(-1, -1) == service.getGhostCoordinates());
			REQUIRE_FALSE(service.getValidLocationForTowerGhost());
		}

		TEST_CASE("beginGhostForPrototype with mouse position in positive sets the ghost tile coordinates as expected", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i TileCoords{ 2,5 };

			const std::string TowerName = "TestTowerName";
			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};

			input.m_GetMousePositionCallback = [&] () { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype({});

			REQUIRE(TileCoords == service.getGhostCoordinates());
		}

		TEST_CASE("beginGhostForPrototype with mouse position in positive outside of surface bounds sets coordinates to nearest within bounds", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i SurfaceSize{ 2,5 };
			const sf::Vector2i TileCoords = { SurfaceSize.x + 1, SurfaceSize.y + 1};

			const std::string TowerName = "TestTowerName";
			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype({});

			REQUIRE(sf::Vector2i(SurfaceSize.x - 1, SurfaceSize.y - 1) == service.getGhostCoordinates());
		}

		TEST_CASE("beginGhostForPrototype with mouse position on valid tile sets location as valid", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i SurfaceSize{ 2,5 };
			const sf::Vector2i TileCoords = { SurfaceSize.x - 1, SurfaceSize.y - 1 };

			const std::string TowerName = "TestTowerName";
			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			surface.canPlace = true;
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype({});

			REQUIRE(service.getValidLocationForTowerGhost());
		}

		TEST_CASE("beginGhostForPrototype with mouse position on invalid tile sets location as invalid", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i SurfaceSize{ 2,5 };
			const sf::Vector2i TileCoords = { SurfaceSize.x - 1, SurfaceSize.y - 1 };

			const std::string TowerName = "TestTowerName";
			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			surface.canPlace = false;
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype({});

			REQUIRE_FALSE(service.getValidLocationForTowerGhost());
		}

		TEST_CASE("attemptPlacingGhost with mouse position on valid tile invokes prototype spawned", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i TileCoords{ 2,5 };
			const sf::Vector2u SurfaceSize{ 3,6 };

			const std::string TowerName = "TestTowerName";

			ParsedTower tower = {};
			tower.prototypeName = TowerName;
			tower.size = { 1,1 };

			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			levelResourceService.canAffordCallback = [](const ResourceBundle&) {return true; };
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			surface.canPlace = true;
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype(tower);

			bool prototypeSpawned = false;
			service.prototypeSpawned = [&](const ParsedTower& _parsedTower, const sf::Vector2i& _coordinates) {
				prototypeSpawned = true;
				REQUIRE(TowerName == _parsedTower.prototypeName);
			};

			REQUIRE(service.attemptPlacingGhost(TileCoords));
			REQUIRE(prototypeSpawned);
		}

		TEST_CASE("attemptPlacingGhost with mouse position on valid tile places prototype on tower placeable surface", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i TileCoords{ 2,5 };
			const sf::Vector2u SurfaceSize{ 3,6 };

			const std::string TowerName = "TestTowerName";

			ParsedTower tower = {};
			tower.prototypeName = TowerName;
			tower.size = { 1,1 };

			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			levelResourceService.canAffordCallback = [](const ResourceBundle&) {return true; };
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			surface.canPlace = true;
			bool placePrototypeInvoked = false;
			surface.placePrototypeCallback = [&](const sf::Vector2i& _coordinates, const ParsedTower& _prototype) {
				placePrototypeInvoked = true;
			};
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype(tower);

			REQUIRE(service.attemptPlacingGhost(TileCoords));
			REQUIRE(placePrototypeInvoked);
		}

		TEST_CASE("attemptPlacingGhost with mouse position on valid tile and where can afford tile pays the prototypes cost", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i TileCoords{ 2,5 };
			const sf::Vector2u SurfaceSize{ 3,6 };

			const std::string TowerName = "TestTowerName";

			ParsedTower tower = {};
			tower.prototypeName = TowerName;
			tower.size = { 1,1 };

			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			levelResourceService.canAffordCallback = [](const ResourceBundle&) { return true; };
			bool payResourceBundleInvoked = false;
			levelResourceService.payResourceBundleCallback = [&](const ResourceBundle&) {
				payResourceBundleInvoked = true;
			};
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			surface.canPlace = true;
			bool placePrototypeInvoked = false;
			surface.placePrototypeCallback = [&](const sf::Vector2i& _coordinates, const ParsedTower& _prototype) {
				placePrototypeInvoked = true;
			};
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype(tower);

			REQUIRE(service.attemptPlacingGhost(TileCoords));
			REQUIRE(payResourceBundleInvoked);
		}

		TEST_CASE("attemptPlacingGhost with mouse position on valid tile when it cannot be affored does not place the prototype", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i TileCoords{ 2,5 };
			const sf::Vector2u SurfaceSize{ 3,6 };

			const std::string TowerName = "TestTowerName";

			ParsedTower tower = {};
			tower.prototypeName = TowerName;
			tower.size = { 1,1 };

			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			bool canAffordCallbackInvoked = false;
			levelResourceService.canAffordCallback = [&](const ResourceBundle&) {
				canAffordCallbackInvoked = true;
				return false;
			};
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			surface.canPlace = true;
			bool placePrototypeInvoked = false;
			surface.placePrototypeCallback = [&](const sf::Vector2i& _coordinates, const ParsedTower& _prototype) {
				placePrototypeInvoked = true;
			};
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype(tower);

			REQUIRE_FALSE(service.attemptPlacingGhost(TileCoords));
			REQUIRE_FALSE(placePrototypeInvoked);
			REQUIRE(canAffordCallbackInvoked);
		}

		TEST_CASE("attemptPlacingGhost with mouse position on invalid tile does not invoke prototype spawned", "[Intrusion][Service][TowerSpawnerService]") {
			const sf::Vector2i TileCoords{ 2,5 };
			const sf::Vector2u SurfaceSize{ 3,6 };

			const std::string TowerName = "TestTowerName";

			ParsedTower tower = {};
			tower.prototypeName = TowerName;
			tower.size = { 1,1 };

			inf::InputManagerMock input;
			inf::LuaManagerMock lua;
			IntrusionConfigurationManagerMock config(lua);
			TowerPlaceableSurfaceServiceMock towerPlaceableSurfaceService;
			LevelResourceServiceMock levelResourceService{};
			TowerPlaceableSurfaceMock surface{};
			surface.width = SurfaceSize.x;
			surface.height = SurfaceSize.y;
			surface.canPlace = false;
			towerPlaceableSurfaceService.setActiveSurface(&surface);

			input.m_GetMousePositionCallback = [&]() { return TileCoords; };
			config.scale = 1.0f;

			TowerSpawnerService service = TowerSpawnerService(input, config, levelResourceService, towerPlaceableSurfaceService);

			service.beginGhostForPrototype(tower);

			bool prototypeSpawned = false;
			service.prototypeSpawned = [&](const ParsedTower& _parsedTower, const sf::Vector2i& _coordinates) {
				prototypeSpawned = true;
			};

			REQUIRE_FALSE(service.attemptPlacingGhost(TileCoords));
			REQUIRE_FALSE(prototypeSpawned);
		}
	}
}
