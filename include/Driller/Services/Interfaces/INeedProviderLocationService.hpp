#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_NEED_PROVIDER_LOCATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_NEED_PROVIDER_LOCATION_SERVICE_HPP_

#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {

	class INeedProviderLocationService {
	protected:
		virtual ~INeedProviderLocationService(void) = 0 {}

	public:
		virtual bool isNeedProviderAvailable(std::size_t _needId) const = 0;
		virtual EntityId getNeedProvider(std::size_t _needId, const sf::Vector2f& _currentPosition) const = 0;

	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_NEED_PROVIDER_LOCATION_SERVICE_HPP_