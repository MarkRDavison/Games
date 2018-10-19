#include <Driller/Services/MarketService.hpp>
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {
	

	MarketService::MarketService(inf::IResourceService& _resourceService) :
		m_ResourceService(_resourceService) {
		
	}
	MarketService::~MarketService(void) {
		
	}

	void MarketService::sellCargo(const inf::ResourceBundle& _cargo) {
		const inf::ResourceBundle& exchangedCargo = applyExchangeRatesToBundle(_cargo);
		m_ResourceService.receiveResourceBundle(exchangedCargo);
	}

	inf::ResourceBundle MarketService::applyExchangeRatesToBundle(const inf::ResourceBundle& _cargo) const {
		inf::ResourceBundle exchanged(_cargo);
		const int oreExchangeRate = m_ResourceService.getResource(Definitions::OreExchangeRateResourceName);
		
		const auto result = std::find_if(exchanged.resources.begin(), exchanged.resources.end(), [](const inf::ResourceBundle::Resource& _resource) { return _resource.name == Definitions::OreResourceName; });
		if (result != exchanged.resources.end()) {
			inf::ResourceBundle::Resource& oreResource = *result;
			oreResource.name = Definitions::MoneyResourceName;
			oreResource.amount = static_cast<int>((static_cast<float>(oreExchangeRate) / Definitions::OreExchangeRateScale + 1.0) * static_cast<float>(oreResource.amount));
		}

		return exchanged;
	}

}
