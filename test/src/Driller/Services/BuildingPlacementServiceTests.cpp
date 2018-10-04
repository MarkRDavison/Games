#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/DataStructures/TerrainRow.hpp>
#include <Driller/Services/BuildingPlacementService.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>
#include <Mocks/Driller/Services/WorkerClassServiceMock.hpp>

namespace drl {
	namespace BuildingPlacementServiceTests {
		
		TEST_CASE("canPlacePrototype returns false when the prototype does not exist", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			const TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);

			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };

			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };

			bool isPrototypeRegisteredInvoked = false;
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				isPrototypeRegisteredInvoked = true;
				return false;
			};

			REQUIRE_FALSE(service.canPlacePrototype(placeBuilding));
			REQUIRE(isPrototypeRegisteredInvoked);
		}

		TEST_CASE("canPlacePrototype returns false when a 1x1 buildings prototype exists but the terrain has not been generated", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			const TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
		
			REQUIRE_FALSE(service.canPlacePrototype(placeBuilding));
		}
		
		TEST_CASE("canPlacePrototype returns false when a 1x1 buildings prototype exists but the terrain has not been dug out", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 0,1 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
		
			TerrainRow& row = terrainData.rows.emplace_back();
			TerrainTile& tile = row.rightTiles.emplace_back();
		
			tile.dugOut = false;
		
			REQUIRE_FALSE(service.canPlacePrototype(placeBuilding));
		}
		
		TEST_CASE("canPlacePrototype returns true when a 1x1 buildings prototype exists but the terrain has been dug out", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {1,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
		
			TerrainRow& row = terrainData.rows.emplace_back();
			TerrainTile& tile = row.rightTiles.emplace_back();
		
			tile.dugOut = true;
		
			REQUIRE(service.canPlacePrototype(placeBuilding));
		}
		
		TEST_CASE("canPlacePrototype returns false when a 1x2 buildings prototype exists but the terrain has been half dug out", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = true;
			row.rightTiles.emplace_back().dugOut = false;
		
			REQUIRE_FALSE(service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns false when a 1x2 buildings prototype exists but the terrain has been half dug out the other way", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = false;
			row.rightTiles.emplace_back().dugOut = true;
		
			REQUIRE_FALSE(service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 2x1 buildings prototype exists and the terrain has been dug out", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = true;
			row.rightTiles.emplace_back().dugOut = true;
		
			REQUIRE(service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 2x1 buildings prototype exists and the terrain has been dug out on the left", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ -2,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = terrainData.rows.emplace_back();
			row.leftTiles.emplace_back().dugOut = true;
			row.leftTiles.emplace_back().dugOut = true;
		
			REQUIRE(service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 2x1 buildings prototype exists and the terrain has not been dug out on the left", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ -2,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			TerrainRow& row = terrainData.rows.emplace_back();
			row.leftTiles.emplace_back().dugOut = false;
			row.leftTiles.emplace_back().dugOut = false;
		
			REQUIRE_FALSE(service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("canPlacePrototype returns true when a 1x2 buildings prototype exists and the terrain has been dug out", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {1,2},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			bool getPrototypeByIdInvoked = false;
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) {
				REQUIRE(placeBuilding.prototypeId == _id);
				getPrototypeByIdInvoked = true;
				return BuildingPrototype;
			};
		
			terrainData.rows.emplace_back().rightTiles.emplace_back().dugOut = true;
			terrainData.rows.emplace_back().rightTiles.emplace_back().dugOut = true;
		
			REQUIRE(service.canPlacePrototype(placeBuilding));
			REQUIRE(getPrototypeByIdInvoked);
		}
		
		TEST_CASE("placePrototype correctly emplaces the building instance on the right side", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ 1,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			bool createInstanceCallbackInvoked = false;
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
			buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {
				createInstanceCallbackInvoked = true;
				return BuildingInstance{};
			};
		
			TerrainRow& row = terrainData.rows.emplace_back();
			row.rightTiles.emplace_back().dugOut = true;
			row.rightTiles.emplace_back().dugOut = true;
		
			service.placePrototype(placeBuilding);
		
			REQUIRE(1 == buildingData.buildings.size());
			REQUIRE(createInstanceCallbackInvoked);
		}
		
		TEST_CASE("placePrototype correctly emplaces the building instance on the left side", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
		
			const std::string PrototypeName = "Name";
			const sf::Vector2i Coordinates{ -2,0 };
			const BuildingPrototype BuildingPrototype{ {2,1},{0,0} };
		
			const GameCommand::PlaceBuildingEvent placeBuilding{ PrototypeName, Coordinates.y, Coordinates.x };
		
			bool createInstanceCallbackInvoked = false;
			buildingPrototypeService.isPrototypeRegisteredByIdCallback = [&](const BuildingPrototypeId& _id) { return true; };
			buildingPrototypeService.getPrototypeByIdCallback = [&](const BuildingPrototypeId& _id) { return BuildingPrototype; };
			buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {
				createInstanceCallbackInvoked = true;
				return BuildingInstance{};
			};
		
			TerrainRow& row = terrainData.rows.emplace_back();
			row.leftTiles.emplace_back().dugOut = true;
			row.leftTiles.emplace_back().dugOut = true;
		
			service.placePrototype(placeBuilding);
		
			REQUIRE(1 == buildingData.buildings.size());
			REQUIRE(createInstanceCallbackInvoked);
		}

		TEST_CASE("placePrototype correctly increases provided prototype id and amount", "[Driller][Services][BuildingPlacementService]") {
			BuildingData buildingData{};
			TerrainData terrainData{};
			BuildingPrototypeServiceMock buildingPrototypeService;
			WorkerClassServiceMock workerClassService;
			BuildingPlacementService service(buildingData, terrainData, buildingPrototypeService, workerClassService);
			BuildingInstance instance{};


			instance.providedWorkerPrototypeAmount = 5;
			instance.providedWorkerPrototypeId = 55u;
			buildingPrototypeService.createInstanceByIdCallback = [&](const BuildingPrototypeId& _id) {
				return instance;
			};

			bool increaseClassMaximumCallbackInvoked = false;
			workerClassService.increaseClassMaximumCallback = [&](const WorkerPrototypeId& _prototypeId, int _amount) {
				REQUIRE(instance.providedWorkerPrototypeId == _prototypeId);
				REQUIRE(instance.providedWorkerPrototypeAmount == _amount);
				increaseClassMaximumCallbackInvoked = true;
			};

			service.placePrototype(GameCommand::PlaceBuildingEvent{});

			REQUIRE(increaseClassMaximumCallbackInvoked);
		}

	}
}
