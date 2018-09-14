#ifndef INCLUDED_INTRUSION_SERVICES_I_WAVE_SPAWNER_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_I_WAVE_SPAWNER_SERVICE_HPP_

#include <functional>

#include <Intrusion/DataStructures/ParsedLevel.hpp>

namespace itr {
	
	class IWaveSpawnerService {
	public:
		virtual ~IWaveSpawnerService(void) = default;

		virtual void update(float _delta) = 0;

		virtual unsigned getCurrentMaximumWaveIndex(void) const = 0;
		virtual unsigned getCurrentMinimumWaveIndex(void) const = 0;
		virtual unsigned getCurrentNumberWavesInProgress(void) const = 0;
		virtual unsigned getEntitiesStillToBeSpawnedThisWaveIndex(void) const = 0;
		virtual unsigned getEntitiesStillToBeSpawned(void) const = 0;

		virtual ParsedLevel getParsedLevel(void) const = 0;

		virtual unsigned getMaximumNumberInProgressWaves(void) const = 0;
		virtual void setMaximumNumberInProgressWaves(unsigned _maximum) = 0;
		virtual void setNumberInProgressWaves(unsigned _number) = 0;

		virtual bool isSpawningComplete(void) const = 0;

		std::function<void(const WaveInstance&)> prototypeSpawned;
		std::function<void(void)> wavesCompleted;
	};

}

#endif // INCLUDED_INTRUSION_SERVICES_I_WAVE_SPAWNER_SERVICE_HPP_