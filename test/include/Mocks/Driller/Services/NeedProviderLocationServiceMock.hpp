#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_NEED_PROVIDER_LOCATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_NEED_PROVIDER_LOCATION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/INeedProviderLocationService.hpp>
#include <Utility/TestSignal.hpp>

namespace drl {

	class NeedProviderLocationServiceMock : public INeedProviderLocationService {
	public:
		~NeedProviderLocationServiceMock(void) override {}

		bool isNeedProviderAvailable(std::size_t _needId) const override {
			return isNeedProviderAvailableCallback(_needId);
		}
		EntityId getNeedProvider(std::size_t _needId, const sf::Vector2f& _currentPosition) const override {
			return getNeedProviderCallback(_needId, _currentPosition);
		}

		inf::TestSignal<bool, std::size_t> isNeedProviderAvailableCallback;
		inf::TestSignal<EntityId, std::size_t, const sf::Vector2f&> getNeedProviderCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_NEED_PROVIDER_LOCATION_SERVICE_MOCK_HPP_