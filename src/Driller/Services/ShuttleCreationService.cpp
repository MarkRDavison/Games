#include <Driller/Services/ShuttleCreationService.hpp>
#include <algorithm>

namespace drl {

	ShuttleCreationService::ShuttleCreationService(ShuttleData& _shuttleData, IShuttlePrototypeService& _shuttlePrototypeService) :
		m_ShuttleData(_shuttleData),
		m_ShuttlePrototypeService(_shuttlePrototypeService) {
		
	}
	ShuttleCreationService::~ShuttleCreationService(void) {
		
	}

	bool ShuttleCreationService::canCreateShuttle(const GameCommand::CreateShuttleEvent& _event) {
		return m_ShuttlePrototypeService.isPrototypeRegistered(_event.prototypeId) && !doesShuttlePrototypeExistAsInstance(_event.prototypeId);
	}
	void ShuttleCreationService::createShuttle(const GameCommand::CreateShuttleEvent& _event) {
		m_ShuttleData.shuttles.push_back(m_ShuttlePrototypeService.createInstance(_event.prototypeId));
		ShuttleInstance& instance = m_ShuttleData.shuttles.back();
	}

	bool ShuttleCreationService::doesShuttlePrototypeExistAsInstance(const ShuttlePrototypeId& _prototypeId) const {
		return std::any_of(m_ShuttleData.shuttles.begin(), m_ShuttleData.shuttles.end(), [_prototypeId](const ShuttleInstance& _instance) { return _instance.prototypeId == _prototypeId; });
	}

}
