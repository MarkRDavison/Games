#ifndef INCLUDED_INTRUSION_SERVICES_WAVE_SPAWNER_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_WAVE_SPAWNER_SERVICE_HPP_

#include <Intrusion/Services/IWaveSpawnerService.hpp>

namespace itr {

	class WaveSpawnerService : public IWaveSpawnerService {
	public:

		static const constexpr unsigned DefaultMaximumNumberInProgressWaves{ 1 };

		WaveSpawnerService(ParsedLevel& _parsedLevel);
		~WaveSpawnerService(void) override;

		void update(float _delta) override;

		unsigned getCurrentMinimumWaveIndex(void) const override;
		unsigned getCurrentMaximumWaveIndex(void) const override; 
		unsigned getEntitiesStillToBeSpawnedThisWaveIndex(void) const override;
		unsigned getEntitiesStillToBeSpawned(void) const override;
		unsigned getCurrentNumberWavesInProgress(void) const override;
		unsigned getMaximumNumberInProgressWaves(void) const override;
		void setMaximumNumberInProgressWaves(unsigned _maximum) override;
		void setNumberInProgressWaves(unsigned _number) override;

		ParsedLevel getParsedLevel(void) const override;
		bool isSpawningComplete(void) const override;

	protected:
		void updateWaveIndex(void);
		void updateEntitiesStillToBeSpawned(void);
		bool isWaveIndexBetweenMinAndMax(unsigned _waveIndex) const;

	private:
		ParsedLevel& m_ParsedLevel;
		unsigned m_CurrentMinimumWaveIndex;
		unsigned m_CurrentMaximumWaveIndex;
		unsigned m_MaximumNumberInProgressWaves;
		unsigned m_EntitiesStillToBeSpawnedThisWaveIndex;
		unsigned m_EntitiesStillToBeSpawned;
	};

}

#endif // INCLUDED_INTRUSION_SERVICES_WAVE_SPAWNER_SERVICE_HPP_