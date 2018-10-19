#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_MARKET_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_MARKET_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IMarketService.hpp>
#include <Utility/TestSignal.hpp>

namespace drl {

	class MarketServiceMock : public IMarketService {
	public:
		~MarketServiceMock(void) override {}
		
		void sellCargo(const inf::ResourceBundle& _cargo) override {
			sellCargoCallback(_cargo);
		}
		inf::ResourceBundle applyExchangeRatesToBundle(const inf::ResourceBundle& _cargo) const override {
			return applyExchangeRatesToBundleCallback(_cargo);
		}

		inf::TestSignal<void, const inf::ResourceBundle&> sellCargoCallback;
		inf::TestSignal<inf::ResourceBundle, const inf::ResourceBundle&> applyExchangeRatesToBundleCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_MARKET_SERVICE_MOCK_HPP_