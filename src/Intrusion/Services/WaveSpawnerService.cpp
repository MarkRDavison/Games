#include <Intrusion/Services/WaveSpawnerService.hpp>
#include <algorithm>

namespace itr {

	WaveSpawnerService::WaveSpawnerService(ParsedLevel& _parsedLevel) :
		m_ParsedLevel(_parsedLevel),
		m_CurrentMinimumWaveIndex(0),
		m_CurrentMaximumWaveIndex(0),
		m_MaximumNumberInProgressWaves(DefaultMaximumNumberInProgressWaves),
		m_EntitiesStillToBeSpawnedThisWaveIndex(0),
		m_EntitiesStillToBeSpawned(0) {
		updateEntitiesStillToBeSpawned();
	}
	WaveSpawnerService::~WaveSpawnerService(void) {

	}

	void WaveSpawnerService::update(float _delta) {
		const std::size_t waves = m_ParsedLevel.waves.size();
		if (waves == 0) {
			if (wavesCompleted) {
				wavesCompleted();
			}
			return;
		}

		bool updateEntitiesRemaining{ false };

		for (WaveInstance& instance : m_ParsedLevel.waves) {
			float instanceDelta = _delta;
			if (isWaveIndexBetweenMinAndMax(instance.waveIndex)) {
				if (instance.time > 0.0f) {
					instance.time -= instanceDelta;
					if (instance.time <= 0.0f) {
						instanceDelta = -instance.time;
						instance.intervalTimer = instance.interval;
					}
				}
				if (instance.time <= 0.0f) {
					instance.intervalTimer -= instanceDelta;
					if (instance.intervalTimer <= 0.0f) {
						instance.intervalTimer += instance.interval;
						instance.amount -= 1;
						if (prototypeSpawned) {
							prototypeSpawned(instance);
							updateEntitiesRemaining = true;
						}
					}
				}
			}
		}

		m_ParsedLevel.waves.erase(std::remove_if(m_ParsedLevel.waves.begin(), m_ParsedLevel.waves.end(),
		[this](const WaveInstance& _waveInstance) {
			return isWaveIndexBetweenMinAndMax(_waveInstance.waveIndex) && _waveInstance.amount <= 0;
		}), m_ParsedLevel.waves.end());

		if (m_ParsedLevel.waves.size() != waves) {
			updateWaveIndex();
		}

		if (updateEntitiesRemaining) {
			updateEntitiesStillToBeSpawned();
		}
	}

	unsigned WaveSpawnerService::getCurrentMinimumWaveIndex(void) const {
		return m_CurrentMinimumWaveIndex;
	}

	unsigned WaveSpawnerService::getCurrentMaximumWaveIndex(void) const {
		return m_CurrentMaximumWaveIndex;
	}

	unsigned WaveSpawnerService::getEntitiesStillToBeSpawnedThisWaveIndex(void) const {
		return m_EntitiesStillToBeSpawnedThisWaveIndex;
	}

	unsigned WaveSpawnerService::getEntitiesStillToBeSpawned(void) const {
		return  m_EntitiesStillToBeSpawned;
	}

	unsigned WaveSpawnerService::getCurrentNumberWavesInProgress(void) const {
		return 1 + m_CurrentMaximumWaveIndex - m_CurrentMinimumWaveIndex;
	}

	unsigned WaveSpawnerService::getMaximumNumberInProgressWaves(void) const {
		return m_MaximumNumberInProgressWaves;
	}
	void WaveSpawnerService::setMaximumNumberInProgressWaves(unsigned _maximum) {
		m_MaximumNumberInProgressWaves = _maximum;
	}

	void WaveSpawnerService::setNumberInProgressWaves(unsigned _number) {
		if (_number > m_MaximumNumberInProgressWaves) {
			_number = m_MaximumNumberInProgressWaves;
		}

		m_CurrentMaximumWaveIndex = m_CurrentMinimumWaveIndex + _number - 1;

		auto maxElement = std::max_element(m_ParsedLevel.waves.begin(), m_ParsedLevel.waves.end(), [](const WaveInstance& _lhs, const WaveInstance& _rhs) {
			return _lhs.waveIndex < _rhs.waveIndex;
		});
		if (maxElement != m_ParsedLevel.waves.end()) {
			const unsigned maxWaveIndex = (*maxElement).waveIndex;

			if (m_CurrentMaximumWaveIndex > maxWaveIndex) {
				m_CurrentMaximumWaveIndex = maxWaveIndex;
			}
		}
	}

	ParsedLevel WaveSpawnerService::getParsedLevel(void) const {
		return m_ParsedLevel;
	}

	bool WaveSpawnerService::isSpawningComplete(void) const {
		return m_ParsedLevel.waves.empty();
	}

	void WaveSpawnerService::updateWaveIndex(void) {
		auto minElement = std::min_element(m_ParsedLevel.waves.begin(), m_ParsedLevel.waves.end(), [](const WaveInstance& _lhs, const WaveInstance& _rhs) {
			return _lhs.waveIndex < _rhs.waveIndex;
		});

		if (minElement != m_ParsedLevel.waves.end()) {
			m_CurrentMinimumWaveIndex = (*minElement).waveIndex;
		}

		if (m_CurrentMaximumWaveIndex < m_CurrentMinimumWaveIndex) {
			m_CurrentMaximumWaveIndex = m_CurrentMinimumWaveIndex;
		}
	}

	void WaveSpawnerService::updateEntitiesStillToBeSpawned(void) {
		m_EntitiesStillToBeSpawnedThisWaveIndex = 0;
		std::for_each(m_ParsedLevel.waves.begin(), m_ParsedLevel.waves.end(), [this](const WaveInstance& _waveInstance) {
			if (isWaveIndexBetweenMinAndMax(_waveInstance.waveIndex)) {
				m_EntitiesStillToBeSpawnedThisWaveIndex += _waveInstance.amount;
			}
			m_EntitiesStillToBeSpawned += _waveInstance.amount;
		});
	}

	bool WaveSpawnerService::isWaveIndexBetweenMinAndMax(unsigned _waveIndex) const {
		return m_CurrentMinimumWaveIndex <= _waveIndex && _waveIndex <= m_CurrentMaximumWaveIndex;
	}

}
