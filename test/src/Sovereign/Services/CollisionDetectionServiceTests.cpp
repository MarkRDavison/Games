#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Sovereign/Services/CollisionDetectionService.hpp>
#include <Sovereign/Core/Definitions.hpp>
#include <Mocks/Sovereign/Services/LevelDataMutationServiceMock.hpp>
#include <Mocks/Sovereign/Services/LevelDataQueryServiceMock.hpp>

namespace sov {
	namespace CollisionDetectionServiceTests {

		struct Package {

			LevelChunk& emplaceEmptyChunk(int _x, int _y) {
				LevelChunk& chunk = levelData.levelChunks.emplace_back();
				chunk.x = _x;
				chunk.y = _y;
				for (unsigned y = 0; y < Definitions::ChunkSize; ++y) {
					for (unsigned x = 0; x < Definitions::ChunkSize; ++x) {
						LevelChunkCell& cell = chunk.cells.emplace_back();
						cell.empty = true;
					}
				}
				return chunk;
			}
			
			Package(void) :
				service(levelData, levelDataMutation, levelDataQuery) {
				
			}

			LevelData levelData{};
			LevelDataMutationServiceMock levelDataMutation;
			LevelDataQueryServiceMock levelDataQuery;
			CollisionDetectionService service;

		};

		TEST_CASE("getCellsContainingEntity for point sized entity returns as expected", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			MoveableEntity entity{};
			entity.position = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };

			const EntityContainedCell& ecc = package.service.getCellsContainingEntity(entity);

			REQUIRE(ecc.valid);
			REQUIRE(0 == ecc.left);
			REQUIRE(0 == ecc.top);
			REQUIRE(1 == ecc.width);
			REQUIRE(1 == ecc.height);
		}

		TEST_CASE("getCellsContainingEntity for entity that is larger than a point but is within the cell returns as expected", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			MoveableEntity entity{};
			entity.position = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };
			entity.size = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };

			const EntityContainedCell& ecc = package.service.getCellsContainingEntity(entity);

			REQUIRE(ecc.valid);
			REQUIRE(0 == ecc.left);
			REQUIRE(0 == ecc.top);
			REQUIRE(1 == ecc.width);
			REQUIRE(1 == ecc.height);
		}

		TEST_CASE("getCellsContainingEntity for entity that goes into another cell horizontally returns as expected", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			MoveableEntity entity{};
			entity.position = { Definitions::TileSize , Definitions::TileSize / 2.0f };
			entity.size = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };

			const EntityContainedCell& ecc = package.service.getCellsContainingEntity(entity);

			REQUIRE(ecc.valid);
			REQUIRE(0 == ecc.left);
			REQUIRE(0 == ecc.top);
			REQUIRE(2 == ecc.width);
			REQUIRE(1 == ecc.height);
		}

		TEST_CASE("getCellsContainingEntity for entity that goes into another cell vertically returns as expected", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			MoveableEntity entity{};
			entity.position = { Definitions::TileSize / 2.0f , Definitions::TileSize };
			entity.size = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };

			const EntityContainedCell& ecc = package.service.getCellsContainingEntity(entity);

			REQUIRE(ecc.valid);
			REQUIRE(0 == ecc.left);
			REQUIRE(0 == ecc.top);
			REQUIRE(1 == ecc.width);
			REQUIRE(2 == ecc.height);
		}

		TEST_CASE("getCellsContainingEntity for entity that goes into another cell vertically and horizontally returns as expected", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			MoveableEntity entity{};
			entity.position = { Definitions::TileSize , Definitions::TileSize };
			entity.size = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };

			const EntityContainedCell& ecc = package.service.getCellsContainingEntity(entity);

			REQUIRE(ecc.valid);
			REQUIRE(0 == ecc.left);
			REQUIRE(0 == ecc.top);
			REQUIRE(2 == ecc.width);
			REQUIRE(2 == ecc.height);
		}

		TEST_CASE("getCellsContainingEntity for entity that goes into another cell vertically and horizontally across the origin returns as expected", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			MoveableEntity entity{};
			entity.position = { 0.0f, 0.0f };
			entity.size = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };

			const EntityContainedCell& ecc = package.service.getCellsContainingEntity(entity);

			REQUIRE(ecc.valid);
			REQUIRE(-1 == ecc.left);
			REQUIRE(-1 == ecc.top);
			REQUIRE(2 == ecc.width);
			REQUIRE(2 == ecc.height);
		}

		TEST_CASE("getCellsContainingEntity for entity that goes into another cell vertically and horizontally where entire entity is in negative coords returns as expected", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			MoveableEntity entity{};
			entity.position = { -Definitions::TileSize , -Definitions::TileSize };
			entity.size = { Definitions::TileSize / 2.0f , Definitions::TileSize / 2.0f };

			const EntityContainedCell& ecc = package.service.getCellsContainingEntity(entity);

			REQUIRE(ecc.valid);
			REQUIRE(-2 == ecc.left);
			REQUIRE(-2 == ecc.top);
			REQUIRE(2 == ecc.width);
			REQUIRE(2 == ecc.height);
		}

		TEST_CASE("detectTileCollisionOccured asks the level data query service if the chunk exists", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			EntityContainedCell ecc{};
			ecc.valid = true;
			ecc.width = 1;
			ecc.height = 1;

			package.levelDataQuery.doesLevelChunkExistCallback.registerCallback([&](int _chunkX, int _chunkY) -> bool {
				REQUIRE(0 == _chunkX);
				REQUIRE(0 == _chunkY);
				return false;
			});

			REQUIRE_FALSE(package.service.detectTileCollisionOccured(ecc));

			REQUIRE(package.levelDataQuery.doesLevelChunkExistCallback.isInvokedOnce());
		}

		TEST_CASE("detectTileCollisionOccured returns false of the cell in question is empty", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			EntityContainedCell ecc{};
			ecc.valid = true;
			ecc.width = 1;
			ecc.height = 1;

			LevelChunkCell cell;
			cell.empty = true;

			package.levelDataQuery.doesLevelChunkExistCallback.registerCallback([&](int _chunkX, int _chunkY) -> bool { return true; });
			package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.registerCallback([&](int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) -> const LevelChunkCell& {
				REQUIRE(0 == _chunkX);
				REQUIRE(0 == _chunkY);
				REQUIRE(ecc.left == _cellX);
				REQUIRE(ecc.top == _cellY);
				return cell;
			});

			REQUIRE_FALSE(package.service.detectTileCollisionOccured(ecc));
			REQUIRE(package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.isInvokedOnce());
		}

		TEST_CASE("detectTileCollisionOccured returns true of the cell in question is not empty", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			EntityContainedCell ecc{};
			ecc.valid = true;
			ecc.width = 1;
			ecc.height = 1;
			ecc.entityBounds.width = 1.0f;
			ecc.entityBounds.height = 1.0f;

			LevelChunkCell cell;
			cell.empty = false;

			package.levelDataQuery.doesLevelChunkExistCallback.registerCallback([&](int _chunkX, int _chunkY) -> bool { return true; });
			package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.registerCallback([&](int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) -> const LevelChunkCell& {
				REQUIRE(0 == _chunkX);
				REQUIRE(0 == _chunkY);
				REQUIRE(ecc.left == _cellX);
				REQUIRE(ecc.top == _cellY);
				return cell;
			});

			REQUIRE(package.service.detectTileCollisionOccured(ecc));
			REQUIRE(package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.isInvokedOnce());
		}

		TEST_CASE("detectTileCollisionOccured looks at all cells if entity spans multiple cells", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			EntityContainedCell ecc{};
			ecc.valid = true;
			ecc.width = 2;
			ecc.height = 2;

			LevelChunkCell cell;
			cell.empty = true;

			package.levelDataQuery.doesLevelChunkExistCallback.registerCallback([&](int _chunkX, int _chunkY) -> bool { return true; });
			package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.registerCallback([&](int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) -> const LevelChunkCell& { return cell; });

			REQUIRE_FALSE(package.service.detectTileCollisionOccured(ecc));

			REQUIRE(package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.isInvokedExactly(ecc.width * ecc.height));
		}

		TEST_CASE("detectTileCollisionOccured looks at all cells if entity spans multiple cells across the origin", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			EntityContainedCell ecc;
			ecc.valid = true;
			ecc.left = -1;
			ecc.top = -1;
			ecc.width = 2;
			ecc.height = 2;

			LevelChunkCell cell;
			cell.empty = true;
			
			package.levelDataQuery.doesLevelChunkExistCallback.registerCallback([&](int _chunkX, int _chunkY) -> bool { return true; });
			package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.registerCallback([&](int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) -> const LevelChunkCell& { return cell; });

			REQUIRE_FALSE(package.service.detectTileCollisionOccured(ecc));

			REQUIRE(package.levelDataQuery.doesLevelChunkExistCallback.isInvokedExactly(ecc.width * ecc.height));
			REQUIRE(package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.isInvokedExactly(ecc.width * ecc.height));
		}

		TEST_CASE("detectTileCollisionOccured sets the intersection bounds correctly when a collision occurs", "[Sovereign][Services][CollisionDetectionService]") {
			Package package{};

			EntityContainedCell ecc{};
			ecc.valid = true;
			ecc.width = 1;
			ecc.height = 1;
			ecc.entityBounds = sf::FloatRect({ Definitions::TileSize / 4.0f, Definitions::TileSize / 4.0f }, { Definitions::TileSize / 2.0f, Definitions::TileSize / 2.0f });

			LevelChunkCell cell;
			cell.empty = false;

			package.levelDataQuery.doesLevelChunkExistCallback.registerCallback([&](int _chunkX, int _chunkY) -> bool { return true; });
			package.levelDataQuery.getLevelChunkCellForLevelChunkCallback.registerCallback([&](int _chunkX, int _chunkY, unsigned _cellX, unsigned _cellY) -> const LevelChunkCell& {
				REQUIRE(0 == _chunkX);
				REQUIRE(0 == _chunkY);
				REQUIRE(ecc.left == _cellX);
				REQUIRE(ecc.top == _cellY);
				return cell;
			});

			sf::FloatRect intersectionBounds{};
			REQUIRE(package.service.detectTileCollisionOccured(ecc, intersectionBounds));

			REQUIRE(ecc.entityBounds == intersectionBounds);
		}
	}
}
