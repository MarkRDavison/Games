#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Services/WaveSpawnerService.hpp>

namespace itr {
	namespace WaveSpawnerServiceTests {

		TEST_CASE("Updating spawner service with an empty parsed level notifies that the spawner service is complete", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			bool wavesCompletedInvoked = false;

			service.allWavesCompleted = [&]() {
				wavesCompletedInvoked = true;
			};

			service.update(1.0f);

			REQUIRE(wavesCompletedInvoked);
		}

		TEST_CASE("Updating spawner service with a single wave with no elapsed time does not notify that the spawner service is complete", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			parsedLevel.waves.emplace_back();
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			bool wavesCompletedInvoked = false;

			service.allWavesCompleted = [&]() {
				wavesCompletedInvoked = true;
			};

			service.update(1.0f);

			REQUIRE_FALSE(wavesCompletedInvoked);
		}

		TEST_CASE("Updating spawner service with a single wave with no delay notifies that a wave instance has been spawned", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			WaveInstance wave{};
			wave.amount = 5;
			wave.waveIndex = 0;
			wave.time = 0.0f;
			wave.interval = 0.0f;
			parsedLevel.waves.push_back(wave);
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			bool waveInstanceSpawned = false;

			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				waveInstanceSpawned = true;
			};

			service.update(0.0f);

			REQUIRE(waveInstanceSpawned);
		}

		TEST_CASE("Updating spawner service with a single wave with node delay and only one spawn removes the wave instance", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			WaveInstance wave{};
			wave.amount = 1;
			wave.waveIndex = 0;
			wave.time = 0.0f;
			wave.interval = 0.0f;
			parsedLevel.waves.push_back(wave);
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			service.update(0.0f);

			const ParsedLevel& pl = service.getParsedLevel();

			REQUIRE(pl.waves.empty());
		}

		TEST_CASE("Updating spawner service with multiple waves with a single spawn all with the same index spawn 1 per wave", "[Intrusion][Service][WaveSpawnerService]") {
			const int SimultaneousWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < SimultaneousWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = 0;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			int wavesSpawned = 0;
			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				wavesSpawned += 1;
			};

			service.update(0.0f);

			REQUIRE(SimultaneousWaves == wavesSpawned);
		}

		TEST_CASE("Updating spawner service with multiple sequential waves spawns each one 1 per update", "[Intrusion][Service][WaveSpawnerService]") {
			const int SequentialWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < SequentialWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = i;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}

			int wavesSpawned = 0;
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);
			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				wavesSpawned += 1;
			};

			for (int i = 0; i < SequentialWaves; ++i) {

				service.update(0.0f);

				REQUIRE(i + 1 == wavesSpawned);
			}
		}

		TEST_CASE("Updating spawner service with 2 parallel waves that last different amount of time doesnt progress to the next wave untill both waves are finished", "[Intrusion][Service][WaveSpawnerService]") {
			const std::string prototypeWave1a = "prototypeWave1a";
			const std::string prototypeWave1b = "prototypeWave1b";
			const std::string prototypeWave2 = "prototypeWave2";
			const int wave1aAmount = 2;
			const int wave1bAmount = 3;
			int spawned1a_count{};
			int spawned1b_count{};
			int spawned2_count{};
			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.time = 0.0f;
				wave.interval = 1.0f;
				wave.amount = wave1aAmount;
				wave.waveIndex = 0;
				wave.entityPrototype = prototypeWave1a;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.time = 0.0f;
				wave.interval = 1.0f;
				wave.amount = wave1bAmount;
				wave.waveIndex = 0;
				wave.entityPrototype = prototypeWave1b;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.time = 0.0f;
				wave.interval = 0.0f;
				wave.amount = 3;
				wave.waveIndex = 1;
				wave.entityPrototype = prototypeWave2;
				parsedLevel.waves.push_back(wave);
			}

			int wavesSpawned = 0;
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);
			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				wavesSpawned += 1;
				if (_waveInstance.entityPrototype == prototypeWave1a) {
					spawned1a_count += 1;
				}
				if (_waveInstance.entityPrototype == prototypeWave1b) {
					spawned1b_count += 1;
				}
				if (_waveInstance.entityPrototype == prototypeWave2) {
					spawned2_count += 1;
				}
			};

			service.update(1.0f);
			service.update(1.0f);
			service.update(1.0f);

			REQUIRE(wave1aAmount + wave1bAmount == wavesSpawned);
			REQUIRE(1 == service.getCurrentMaximumWaveIndex());
			REQUIRE(wave1aAmount == spawned1a_count);
			REQUIRE(wave1bAmount == spawned1b_count);
			REQUIRE(0 == spawned2_count);
		}

		TEST_CASE("Updating spawner service with single wave with delay and interval correctly waits to spawn", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			WaveInstance wave{};
			wave.amount = 5;
			wave.waveIndex = 0;
			wave.time = 2.0f;
			wave.interval = 1.0f;
			parsedLevel.waves.push_back(wave);
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			int waveInstanceSpawned = 0;

			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				waveInstanceSpawned += 1;
			};

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(1 == waveInstanceSpawned);

			service.update(0.5f);
			REQUIRE(1 == waveInstanceSpawned);

			service.update(0.5f);
			REQUIRE(2 == waveInstanceSpawned);

			service.update(0.5f);
			REQUIRE(2 == waveInstanceSpawned);

			service.update(0.5f);
			REQUIRE(3 == waveInstanceSpawned);
		}
		
		TEST_CASE("Updating spawner service with multiple sequential waves with delay and interval correctly waits to spawn", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 0;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 1;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			int waveInstanceSpawned = 0;

			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				waveInstanceSpawned += 1;
			};

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(1 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(2 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(2 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(2 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(3 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(4 == waveInstanceSpawned);
		}
		
		TEST_CASE("Updating spawner service with multiple parallel waves with delay and interval correctly waits to spawn", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 0;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 0;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			int waveInstanceSpawned = 0;

			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				waveInstanceSpawned += 1;
			};

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(2 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(4 == waveInstanceSpawned);
		}

		TEST_CASE("Updating spawner service with multiple parallel and sequential waves with delay and interval correctly waits to spawn", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 0;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 1;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 1;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 2;
				wave.waveIndex = 2;
				wave.time = 2.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			int waveInstanceSpawned = 0;

			service.prototypeSpawned = [&](const WaveInstance& _waveInstance) {
				waveInstanceSpawned += 1;
			};

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(0 == waveInstanceSpawned);


			service.update(1.0f);
			REQUIRE(1 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(2 == waveInstanceSpawned);


			service.update(1.0f);
			REQUIRE(2 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(2 == waveInstanceSpawned);


			service.update(1.0f);
			REQUIRE(4 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(6 == waveInstanceSpawned);


			service.update(1.0f);
			REQUIRE(6 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(6 == waveInstanceSpawned);


			service.update(1.0f);
			REQUIRE(7 == waveInstanceSpawned);

			service.update(1.0f);
			REQUIRE(8 == waveInstanceSpawned);
		}

		TEST_CASE("Spawner service says spawning is still in progress when 1 wave instance is present", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			parsedLevel.waves.emplace_back();
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			REQUIRE_FALSE(service.isSpawningComplete());
		}

		TEST_CASE("Spawner service says waspawningve is complete 0 wave instances are present", "[Intrusion][Service][WaveSpawnerService]") {
			ParsedLevel parsedLevel{};
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			REQUIRE(service.isSpawningComplete());
		}

		TEST_CASE("Spawner service gets correct number of entities remaining in current wave with one wave instance", "[Intrusion][Service][WaveSpawnerService]") {
			const int Number = 5;
			ParsedLevel parsedLevel{};
			WaveInstance wave{};
			wave.amount = Number;
			parsedLevel.waves.push_back(wave);
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			REQUIRE(Number == service.getEntitiesStillToBeSpawnedThisWaveIndex());
		}

		TEST_CASE("Spawner service gets correct number of entities remaining in current wave with two wave instances from the same wave index", "[Intrusion][Service][WaveSpawnerService]") {
			const int Number1 = 5;
			const int Number2 = 5;
			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = Number1;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = Number2;
				parsedLevel.waves.push_back(wave);
			}
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			REQUIRE(Number1 + Number2 == service.getEntitiesStillToBeSpawnedThisWaveIndex());
		}

		TEST_CASE("Spawner service gets correct number of entities remaining in current wave with two wave instances from different wave index", "[Intrusion][Service][WaveSpawnerService]") {
			const int Number1 = 5;
			const int Number2 = 5;
			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = Number1;
				wave.waveIndex = 0;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = Number2;
				wave.waveIndex = 1;
				parsedLevel.waves.push_back(wave);
			}
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			REQUIRE(Number1 == service.getEntitiesStillToBeSpawnedThisWaveIndex());
		}

		TEST_CASE("Spawner service gets correct number of entities remaining in total with two wave instances from different wave index", "[Intrusion][Service][WaveSpawnerService]") {
			const int Number1 = 5;
			const int Number2 = 5;
			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = Number1;
				wave.waveIndex = 0;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = Number2;
				wave.waveIndex = 1;
				parsedLevel.waves.push_back(wave);
			}
			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			REQUIRE(Number1 + Number2 == service.getEntitiesStillToBeSpawned());
		}
		
		TEST_CASE("When spawner is updated with no other input minimum and maximum wave index are always in sync for sequential waves", "[Intrusion][Service][WaveSpawnerService]") {
			const int SequentialWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < SequentialWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = i;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			for (int i = 0; i < SequentialWaves; ++i) {

				service.update(0.0f);

				REQUIRE(service.getCurrentMinimumWaveIndex() == service.getCurrentMaximumWaveIndex());
			}
		}

		TEST_CASE("When spawner is updated with no other input minimum and maximum wave index are always in sync for parallel waves", "[Intrusion][Service][WaveSpawnerService]") {
			const int ParallelWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < ParallelWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = 0;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			for (int i = 0; i < ParallelWaves; ++i) {

				service.update(0.0f);

				REQUIRE(service.getCurrentMinimumWaveIndex() == service.getCurrentMaximumWaveIndex());
			}
		}

		TEST_CASE("When spawner is updated with no other input minimum and maximum wave index are always in sync for sequential and parallel waves", "[Intrusion][Service][WaveSpawnerService]") {
			const int ParallelWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < ParallelWaves; ++i) {
				for (int j = 0; j < ParallelWaves; ++j) {
					WaveInstance wave{};
					wave.amount = 1;
					wave.waveIndex = i;
					wave.time = 0.0f;
					wave.interval = 0.0f;
					parsedLevel.waves.push_back(wave);
				}
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			for (int i = 0; i < ParallelWaves * ParallelWaves; ++i) {

				service.update(0.0f);

				REQUIRE(service.getCurrentMinimumWaveIndex() == service.getCurrentMaximumWaveIndex());
			}
		}
		
		TEST_CASE("When spawner triggers an extra wave the maximum wave index is greater than the minimum", "[Intrusion][Service][WaveSpawnerService]") {
			const int NumberInProgressWaves = 2;
			const int SequentialWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < SequentialWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = i;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			service.setMaximumNumberInProgressWaves(NumberInProgressWaves);

			service.setNumberInProgressWaves(NumberInProgressWaves);

			REQUIRE(service.getCurrentMinimumWaveIndex() < service.getCurrentMaximumWaveIndex());
			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());
		}

		TEST_CASE("Spawner can only have a certain maximum number of waves in progress simultaneously", "[Intrusion][Service][WaveSpawnerService]") {
			const int NumberInProgressWaves = 2;
			const int SequentialWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < SequentialWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = i;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			service.setMaximumNumberInProgressWaves(NumberInProgressWaves);

			service.setNumberInProgressWaves(NumberInProgressWaves + NumberInProgressWaves);

			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());
		}

		TEST_CASE("Spawner returns the correct number of in progress waves when maximum in a row are triggered", "[Intrusion][Service][WaveSpawnerService]") {
			const int NumberInProgressWaves = 5;
			const int SequentialWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < SequentialWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = i;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			service.setMaximumNumberInProgressWaves(NumberInProgressWaves);

			while (service.getCurrentNumberWavesInProgress() < service.getMaximumNumberInProgressWaves()) {
				service.setNumberInProgressWaves(1 + service.getCurrentNumberWavesInProgress());
			}

			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());
		}

		TEST_CASE("Spawner returns the correct number of in progress waves when maximum in a row are triggered and the middle one finishes", "[Intrusion][Service][WaveSpawnerService]") {
			const int NumberInProgressWaves = 3;

			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = 4;
				wave.waveIndex = 0;
				wave.time = 0.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = 1;
				wave.time = 0.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 4;
				wave.waveIndex = 2;
				wave.time = 0.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			service.setMaximumNumberInProgressWaves(NumberInProgressWaves);
			service.setNumberInProgressWaves(NumberInProgressWaves);

			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());
			
			service.update(1.0f);

			REQUIRE(2 == service.getParsedLevel().waves.size());
			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());
		}

		TEST_CASE("If max number of simultaneous waves are running and one in the middle finishes another cannot be triggered until the minimum wave finishes", "[Intrusion][Service][WaveSpawnerService]") {
			const int NumberInProgressWaves = 3;

			ParsedLevel parsedLevel{};
			{
				WaveInstance wave{};
				wave.amount = 4;
				wave.waveIndex = 0;
				wave.time = 0.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = 1;
				wave.time = 0.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}
			{
				WaveInstance wave{};
				wave.amount = 4;
				wave.waveIndex = 2;
				wave.time = 0.0f;
				wave.interval = 1.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			service.setMaximumNumberInProgressWaves(NumberInProgressWaves + 1);
			service.setNumberInProgressWaves(NumberInProgressWaves);

			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());

			service.update(1.0f);

			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());
			service.setNumberInProgressWaves(NumberInProgressWaves);
			REQUIRE(NumberInProgressWaves == service.getCurrentNumberWavesInProgress());
		}
		
		TEST_CASE("Cannot trigger another wave if there arent anymore to trigger", "[Intrusion][Service][WaveSpawnerService]") {
			const int NumberInProgressWaves = 10;
			const int SequentialWaves = 5;
			ParsedLevel parsedLevel{};
			for (int i = 0; i < SequentialWaves; ++i) {
				WaveInstance wave{};
				wave.amount = 1;
				wave.waveIndex = i;
				wave.time = 0.0f;
				wave.interval = 0.0f;
				parsedLevel.waves.push_back(wave);
			}

			WaveSpawnerService service;
			service.setParsedLevel(parsedLevel);

			service.setMaximumNumberInProgressWaves(NumberInProgressWaves);
			service.setNumberInProgressWaves(NumberInProgressWaves);

			REQUIRE(SequentialWaves == service.getCurrentNumberWavesInProgress());
		}
	}
}