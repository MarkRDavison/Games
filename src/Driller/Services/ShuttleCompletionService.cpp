#include <Driller/Services/ShuttleCompletionService.hpp>
#include <algorithm>

namespace drl {

	ShuttleCompletionService::ShuttleCompletionService(ShuttleData& _shuttleData, IMarketService& _marketService, IShuttleDepartureService& _shuttleDepartureService) :
		m_ShuttleData(_shuttleData),
		m_MarketService(_marketService),
		m_ShuttleDepartureService(_shuttleDepartureService) {
		
	}

	ShuttleCompletionService::~ShuttleCompletionService(void) {
		
	}


	void ShuttleCompletionService::handleShuttleCompleted(ShuttleInstance& _shuttle) {
		m_MarketService.sellCargo(_shuttle.cargo);
		m_ShuttleDepartureService.setShuttleOnRun(false);
		_shuttle.removalRequired = true;
		m_ShuttleRemoved = true;
	}

	void ShuttleCompletionService::cleanupCompletedShuttles(void) {
		if (m_ShuttleRemoved) {
			m_ShuttleRemoved = false;
			m_ShuttleData.shuttles.erase(std::remove_if(m_ShuttleData.shuttles.begin(), m_ShuttleData.shuttles.end(), [](const ShuttleInstance& _shuttle) -> bool {
				return _shuttle.removalRequired;
			}), m_ShuttleData.shuttles.end());
		}
	}

}
