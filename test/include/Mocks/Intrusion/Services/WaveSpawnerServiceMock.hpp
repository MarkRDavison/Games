#ifndef INCLUDED_MOCKS_INTRUSION_SERVICES_WAVE_SPAWNER_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_INTRUSION_SERVICES_WAVE_SPAWNER_SERVICE_MOCK_HPP_

#include <functional>

#include <Intrusion/Services/IWaveSpawnerService.hpp>

namespace itr {

	class WaveSpawnerServiceMock : public IWaveSpawnerService {
	public:
		~WaveSpawnerServiceMock(void) override {
			
		}

		void update(float _delta) override {
			if (updateCallback) {
				updateCallback(_delta);
			}
		}

		unsigned getCurrentMinimumWaveIndex(void) const override {
			return currentMinimumWaveIndex;
		}
		unsigned getCurrentMaximumWaveIndex(void) const override {
			return currentMaximumWaveIndex;
		}
		unsigned getEntitiesStillToBeSpawnedThisWaveIndex(void) const override {
			return entitiesStillToBeSpawnedThisWaveIndex;
		}
		unsigned getEntitiesStillToBeSpawned(void) const override {
			return entitiesStillToBeSpawned;
		}
		unsigned getCurrentNumberWavesInProgress(void) const override {
			return currentNumberWavesInProgress;
		}
		unsigned getMaximumNumberInProgressWaves(void) const override {
			return maximumNumberInProgressWaves;
		}
		void setMaximumNumberInProgressWaves(unsigned _maximum) override {
			maximumNumberInProgressWaves = _maximum;
		}
		void setNumberInProgressWaves(unsigned _number) override {
			numberInProgressWaves = _number;
		}
		void setParsedLevel(const ParsedLevel& _parsedLevel) override {
			parsedLevel = _parsedLevel;
		}

		ParsedLevel getParsedLevel(void) const override {
			return parsedLevel;
		}

		bool isSpawningComplete(void) const override {
			return isSpawningCompleted;
		}
		std::function<void(float)> updateCallback;
		unsigned currentMaximumWaveIndex{ 0 };
		unsigned currentMinimumWaveIndex{ 0 };
		unsigned entitiesStillToBeSpawnedThisWaveIndex{ 0 };
		unsigned entitiesStillToBeSpawned{ 0 };
		unsigned maximumNumberInProgressWaves{ 0 };
		unsigned currentNumberWavesInProgress{ 0 };
		unsigned numberInProgressWaves{ 0 };
		bool isSpawningCompleted{ false };
		ParsedLevel parsedLevel{};
	};

}

#endif // INCLUDED_MOCKS_INTRUSION_SERVICES_WAVE_SPAWNER_SERVICE_MOCK_HPP_