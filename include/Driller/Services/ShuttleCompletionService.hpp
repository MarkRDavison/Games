#ifndef INCLUDED_DRILLER_SERVICES_SHUTTLE_COMPLETION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SHUTTLE_COMPLETION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IShuttleCompletionService.hpp>
#include <Driller/Services/Interfaces/IMarketService.hpp>
#include <Driller/DataStructures/ShuttleData.hpp>
#include "Interfaces/IShuttleDepartureService.hpp"

namespace drl {
	
	class ShuttleCompletionService : public IShuttleCompletionService {
	public:
		ShuttleCompletionService(ShuttleData& _shuttleData, IMarketService& _marketService, IShuttleDepartureService& _shuttleDepartureService);
		~ShuttleCompletionService(void) override;

		void handleShuttleCompleted(ShuttleInstance& _shuttle) override;
		void cleanupCompletedShuttles(void) override;

	private:
		ShuttleData& m_ShuttleData;
		IMarketService& m_MarketService;
		IShuttleDepartureService& m_ShuttleDepartureService;
		bool m_ShuttleRemoved{ false };
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SHUTTLE_COMPLETION_SERVICE_HPP_