#ifndef INCLUDED_DRILLER_SERVICES_MARKET_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_MARKET_SERVICE_HPP_

#include <Driller/Services/Interfaces/IMarketService.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>

namespace drl {
	
	class MarketService : public IMarketService {
	public:
		MarketService(inf::IResourceService& _resourceService);
		~MarketService(void) override;

		void sellCargo(const inf::ResourceBundle& _cargo) override;

	private:
		inf::IResourceService& m_ResourceService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_MARKET_SERVICE_HPP_