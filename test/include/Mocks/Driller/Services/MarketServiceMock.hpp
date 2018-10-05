#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_MARKET_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_MARKET_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IMarketService.hpp>
#include <functional>

namespace drl {

	class MarketServiceMock : public IMarketService {
	public:
		~MarketServiceMock(void) override {}
		
		void sellCargo(const inf::ResourceBundle& _cargo) override {
			if (sellCargoCallback) {
				sellCargoCallback(_cargo);
			}
		}

		std::function<void(const inf::ResourceBundle&)> sellCargoCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_MARKET_SERVICE_MOCK_HPP_