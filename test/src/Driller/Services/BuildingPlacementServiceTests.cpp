#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/DataStructures/TerrainRow.hpp>
#include <Driller/Services/BuildingPlacementService.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>
#include <Mocks/Driller/Services/WorkerClassServiceMock.hpp>
#include <Mocks/Driller/Services/TerrainAlterationServiceMock.hpp>
#include <Driller/DataStructures/TerrainData.hpp>
#include <Mocks/Driller/Services/ShuttleDepartureServiceMock.hpp>

namespace drl {
	namespace BuildingPlacementServiceTests {

		struct Package {

			Package(void) :
				service(buildingData, terrainAlterationService, buildingPrototypeService, workerClassService, shuttleDepartureService) {

				terrainAlterationService.doesTileExistCallback = [this](int _level, int _column) -> bool { return terrainData.tileExists(_level, _column); };
				terrainAlterationService.getTileCallback = [this](int _level, int _column) -> TerrainTile& { return terrainData.getTile(_level, _column); };
			}

			BuildingData buildingData;
			TerrainData terrainData;
			TerrainAlterationServiceMock terrainAlterationService;
			BuildingPrototypeServiceMock buildingPrototypeService;
			ShuttleDepartureServiceMock shuttleDepartureService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service;
			
		};
		
		TEST_CASE("canPlacePrototype returns false when the prototype does not exist", "[Driller][Services][BuildingPlacementService]") {
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			bool isPrototypeRegisteredInvoked = false;
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				isPrototypeRegisteredInvoked = true;
				return false;
			};

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
			REQUIRE(isPrototypeRegisteredInvoked);
		}

		TEST_CASE("canPlacePrototype returns false when a 1x1 buildings prototype exists but the terrain has not been generated", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
		
			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
		}
		
		TEST_CASE("canPlacePrototype returns false when a 1x1 buildings prototype exists but the terrain has not been dug out", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			TerrainTile& tile = row.rightTiles.emplace_back();
		
			tile.dugOut = false;
		
			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
		}
		
		TEST_CASE("canPlacePrototype returns true when a 1x1 buildings prototype exists but the terrain has been dug out", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			TerrainTile& tile = row.rightTiles.emplace_back();
		
			tile.dugOut = true;
		
			REQUIRE(package.service.canPlacePrototype(placeBuilding));
		}
		
		TEST_CASE("canPlacePrototype returns false when a 1x2 buildings prototype exists but the terrain has been half dug out", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = true;
			row.rightTiles.emplace_back().dugOut = false;
		
			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns false when a 1x2 buildings prototype exists but the terrain has been half dug out the other way", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = false;
			row.rightTiles.emplace_back().dugOut = true;
		
			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 2x1 buildings prototype exists and the terrain has been dug out", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = true;
			row.rightTiles.emplace_back().dugOut = true;
		
			REQUIRE(package.service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 2x1 buildings prototype exists and the terrain has been dug out on the left", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ -2,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.leftTiles.emplace_back().dugOut = true;
			row.leftTiles.emplace_back().dugOut = true;
		
			REQUIRE(package.service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 2x1 buildings prototype exists and the terrain has not been dug out on the left", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ -2,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.leftTiles.emplace_back().dugOut = false;
			row.leftTiles.emplace_back().dugOut = false;
		
			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 1x2 buildings prototype exists and the terrain has been dug out", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {1,2},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			package.terrainData.rows.emplace_back().rightTiles.emplace_back().dugOut = true;
			package.terrainData.rows.emplace_back().rightTiles.emplace_back().dugOut = true;
		
			REQUIRE(package.service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}

		TEST_CASE("placePrototype correctly emplaces the building instance on the right side", "[Driller][Services][BuildingPlacementService]") {
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			bool createInstanceCallbackInvoked = false;
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
			package.buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {
				createInstanceCallbackInvoked = true;
				return BuildingInstance{};
			};

			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = true;
			row.rightTiles.emplace_back().dugOut = true;

			package.service.placePrototype(placeBuilding);

			REQUIRE(1 == package.buildingData.buildings.size());
			REQUIRE(createInstanceCallbackInvoked);
		}

		TEST_CASE("placePrototype places a building on the terrain tiles", "[Driller][Services][BuildingPlacementService]") {
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
			BuildingInstance instance;
			instance.size = BuildingPrototype.size;

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
			package.buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {	return instance; };

			bool placeBuildingOnTileCallbackInvoked = false;
			package.terrainAlterationService.placeBuildingOnTileCallback = [&](int _level, int _column, bool _placeBuilding) -> void {
				REQUIRE(Coordinates.y == _level);
				REQUIRE((Coordinates.x == _column || Coordinates.x + 1 == _column));
				REQUIRE(_placeBuilding);
				placeBuildingOnTileCallbackInvoked = true;
			};

			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = true;
			row.rightTiles.emplace_back().dugOut = true;

			package.service.placePrototype(placeBuilding);

			REQUIRE(placeBuildingOnTileCallbackInvoked);
		}
		
		TEST_CASE("placePrototype correctly emplaces the building instance on the left side", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ -2,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			bool createInstanceCallbackInvoked = false;
			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
			package.buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {
				createInstanceCallbackInvoked = true;
				return BuildingInstance{};
			};
		
			TerrainRow& row = package.terrainData.rows.emplace_back();
			row.leftTiles.emplace_back().dugOut = true;
			row.leftTiles.emplace_back().dugOut = true;
		
			package.service.placePrototype(placeBuilding);
		
			REQUIRE(1 == package.buildingData.buildings.size());
			REQUIRE(createInstanceCallbackInvoked);
		}

		TEST_CASE("placePrototype correctly increases provided prototype id and amount", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
			BuildingInstance instance{};


			instance.providedWorkerPrototypeAmount = 5;
			instance.providedWorkerPrototypeId = 55u;
			package.buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {
				return instance;
			};

			bool increaseClassMaximumCallbackInvoked = false;
			package.workerClassService.increaseClassMaximumCallback = [&](const WorkerPrototypeId& _prototypeId, int _amount) {
				REQUIRE(instance.providedWorkerPrototypeId == _prototypeId);
				REQUIRE(instance.providedWorkerPrototypeAmount == _amount);
				increaseClassMaximumCallbackInvoked = true;
			};

			package.service.placePrototype(GameCommand::PlaceBuildingEvent{});

			REQUIRE(increaseClassMaximumCallbackInvoked);
		}

		TEST_CASE("Tiles that been reserved by a job cannot be used to place buildings on", "[Driller][Services][BuildingPlacementService]") {
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };

			TerrainRow& row = package.terrainData.rows.emplace_back();
			TerrainTile& tile = row.rightTiles.emplace_back();

			tile.dugOut = true;
			tile.jobReserved = true;

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
		}

		TEST_CASE("Tiles that have a building on them cannot be used to place buildings on", "[Driller][Services][BuildingPlacementService]") {
			Package package{};

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			package.buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			package.buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };

			TerrainRow& row = package.terrainData.rows.emplace_back();
			TerrainTile& tile = row.rightTiles.emplace_back();

			tile.dugOut = true;
			tile.jobReserved = false;
			tile.hasBuilding = true;

			REQUIRE_FALSE(package.service.canPlacePrototype(placeBuilding));
		}
		
		TEST_CASE("placePrototype invokes addWorkerPrototypeToQueue on the shuttle departure service", "[Driller][Services][BuildingPlacementService]") {
			Package package{};
			BuildingInstance instance{};


			instance.providedWorkerPrototypeAmount = 5;
			instance.providedWorkerPrototypeId = 55u;
			package.buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {
				return instance;
			};

			bool addWorkerPrototypeToQueueCallbackInvoked = false;
			package.shuttleDepartureService.addWorkerPrototypeToQueueCallback = [&](const WorkerPrototypeId& _prototypeId) -> void {
				REQUIRE(instance.providedWorkerPrototypeId == _prototypeId);
				addWorkerPrototypeToQueueCallbackInvoked = true;
			};

			package.service.placePrototype(GameCommand::PlaceBuildingEvent{});

			REQUIRE(addWorkerPrototypeToQueueCallbackInvoked);
		}

	}
}
