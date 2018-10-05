#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Core/Game.hpp>
#include <Mocks/Driller/Services/GameCommandServiceMock.hpp>
#include <Mocks/Driller/Services/JobAllocationServiceMock.hpp>
#include <Mocks/Driller/Services/WorkerUpdateServiceMock.hpp>
#include <Mocks/Driller/Services/JobCompletionServiceMock.hpp>
#include <Mocks/Driller/Services/ShuttleDepartureServiceMock.hpp>
#include <Mocks/Driller/Services/ShuttleUpdateServiceMock.hpp>
#include <Mocks/Driller/Services/ShuttleCompletionServiceMock.hpp>

namespace drl {
	namespace GameTests {
		
		TEST_CASE("", "[Driller][Core][Game]") {
			TerrainData terrainData{};
			BuildingData buildingData{};
			JobData jobData{};
			WorkerData workerData{};

			GameCommandServiceMock gameCommandService;
			JobAllocationServiceMock jobAllocationService;
			JobCompletionServiceMock jobCompletionService;
			WorkerUpdateServiceMock workerUpdateService;
			ShuttleDepartureServiceMock shuttleDepartureService;
			ShuttleUpdateServiceMock shuttleUpdateService;
			ShuttleCompletionServiceMock shuttleCompletionService;

			Game game(gameCommandService, jobAllocationService, jobCompletionService, workerUpdateService, shuttleDepartureService, shuttleUpdateService, shuttleCompletionService, terrainData, buildingData, jobData, workerData);
		}

	}
}
