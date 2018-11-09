#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_MARKET_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_MARKET_SERVICE_HPP_

#include <Infrastructure/DataStructures/ResourceBundle.hpp>

namespace drl {
	
	class IMarketService {
	public:
		virtual ~IMarketService(void) = 0;

		virtual void sellCargo(const inf::ResourceBundle& _cargo) = 0;
		virtual inf::ResourceBundle applyExchangeRatesToBundle(const inf::ResourceBundle& _cargo) const = 0;
	};

	inline IMarketService::~IMarketService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_MARKET_SERVICE_HPP_