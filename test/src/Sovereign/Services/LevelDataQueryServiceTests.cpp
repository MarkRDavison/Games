#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Sovereign/Services/LevelDataQueryService.hpp>
#include <Sovereign/Core/Definitions.hpp>

namespace sov {
	namespace LevelDataQueryServiceTests {

		struct Package {
			
			Package(void) :
				service(levelData) {
				
			}

			LevelData levelData;
			LevelDataQueryService service;

		};

		TEST_CASE("doesLevelChunkExist returns false if the x/y coordinates of the chunk do not exist", "[Sovereign][Services][LevelDataQueryService]") {
			Package package{};

			REQUIRE_FALSE(package.service.doesLevelChunkExist(0, 0));
		}

		TEST_CASE("doesLevelChunkExist returns true if the x/y coordinates of the chunk exist", "[Sovereign][Services][LevelDataQueryService]") {
			Package package{};

			LevelChunk& chunk = package.levelData.levelChunks.emplace_back();
			chunk.x = 0;
			chunk.y = 0;

			REQUIRE(package.service.doesLevelChunkExist(0, 0));
		}

		TEST_CASE("getLevelChunkCellForLevelChunk returns the expected cell for positive cell coordinates", "[Sovereign][Services][LevelDataQueryService]") {
			Package package{};

			LevelChunk& chunk = package.levelData.levelChunks.emplace_back();
			chunk.x = 0;
			chunk.y = 0;

			LevelChunkCell& cell = chunk.cells.emplace_back();

			const LevelChunkCell& resultCell = package.service.getLevelChunkCellForLevelChunk(0, 0, 0, 0);

			REQUIRE(&cell == &resultCell);
		}

		TEST_CASE("getLevelChunkCellForLevelChunk returns the expected cell for negative cell coordinates", "[Sovereign][Services][LevelDataQueryService]") {
			Package package{};

			const sf::Vector2i absoluteCellCoordinates{ -1, -1 };
			const sf::Vector2i relativeCellCoordinates{ 11, 11 };

			LevelChunk& chunk = package.levelData.levelChunks.emplace_back();
			chunk.x = -1;
			chunk.y = -1;

			for (unsigned i = 0; i < Definitions::ChunkSize * Definitions::ChunkSize; ++i) {
				chunk.cells.emplace_back();
			}

			const LevelChunkCell& cell = chunk.cells[relativeCellCoordinates.y * Definitions::ChunkSize + relativeCellCoordinates.x];

			const LevelChunkCell& resultCell = package.service.getLevelChunkCellForLevelChunk(-1, -1, Definitions::ChunkSize + absoluteCellCoordinates.x, Definitions::ChunkSize + absoluteCellCoordinates.y);

			REQUIRE(&cell == &resultCell);
		}
	}
}
