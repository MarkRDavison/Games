#include <Driller/Services/ShuttleDepartureService.hpp>

namespace drl {

	ShuttleDepartureService::ShuttleDepartureService(IShuttleCreationService& _shuttleCreationService) :
		m_ShuttleCreationService(_shuttleCreationService) {
		
	}

	ShuttleDepartureService::~ShuttleDepartureService(void) {
		
	}

	void ShuttleDepartureService::update(float _delta) {
		if (!m_OnRun) {
			m_AccumulatedTime += _delta;
			if (m_AccumulatedTime >= m_DepartureInterval) {
				m_AccumulatedTime -= m_DepartureInterval;
				GameCommand::CreateShuttleEvent event{};
				event.prototypeId = m_PrototypeId;
				if (m_ShuttleCreationService.canCreateShuttle(event)) {
					m_ShuttleCreationService.createShuttle(event);
					setShuttleOnRun(true);
				}
			}
		}
	}

	void ShuttleDepartureService::registerShuttle(const ShuttlePrototypeId& _prototypeId, float _departureInterval) {
		m_PrototypeId = _prototypeId;
		m_DepartureInterval = _departureInterval;
		m_AccumulatedTime = 0.0f;
	}

	ShuttlePrototypeId ShuttleDepartureService::getCurrentPrototypeId(void) const {
		return m_PrototypeId;
	}
	float ShuttleDepartureService::getCurrentDepartureInterval(void) const {
		return m_DepartureInterval;
	}

	void ShuttleDepartureService::addWorkerPrototypeToQueue(const WorkerPrototypeId& _workerPrototypeId) {
		m_WorkersToCarry.push_back(_workerPrototypeId);
	}
	WorkerPrototypeId ShuttleDepartureService::peekWorkerPrototypeQueue(int _failedPeeks) const {
		return m_WorkersToCarry[static_cast<unsigned>(_failedPeeks)];
	}
	void ShuttleDepartureService::popWorkerPrototoypeQueue(int _failedPeeks) {
		m_WorkersToCarry.erase(m_WorkersToCarry.begin() + static_cast<unsigned>(_failedPeeks));
	}
	bool ShuttleDepartureService::workerPrototypeQueueEmpty(int _failedPeeks) const {
		return m_WorkersToCarry.size() <= static_cast<unsigned>(_failedPeeks);
	}

	void ShuttleDepartureService::setShuttleOnRun(bool _onRun) {
		m_OnRun = _onRun;
		if (!_onRun) {
			m_AccumulatedTime = 0.0f;
		}
	}

	bool ShuttleDepartureService::getShuttleOnRun(void) const {
		return m_OnRun;
	}

}
