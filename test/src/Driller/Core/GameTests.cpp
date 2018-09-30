#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Core/Game.hpp>
#include <Mocks/Driller/Services/GameCommandServiceMock.hpp>
#include <Mocks/Driller/Services/JobAllocationServiceMock.hpp>
#include <Mocks/Driller/Services/WorkerUpdateServiceMock.hpp>

namespace drl {
	namespace GameTests {
		
		TEST_CASE("", "[Driller][Core][Game]") {
			TerrainData terrainData{};
			BuildingData buildingData{};
			JobData jobData{};
			WorkerData workerData{};

			GameCommandServiceMock gameCommandService;
			JobAllocationServiceMock jobAllocationService;
			WorkerUpdateServiceMock workerUpdateService;

			Game game(gameCommandService, jobAllocationService, workerUpdateService, terrainData, buildingData, jobData, workerData);
		}

	}
}
