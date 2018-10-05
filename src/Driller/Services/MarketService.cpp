#include <Driller/Services/MarketService.hpp>

namespace drl {
	

	MarketService::MarketService(inf::IResourceService& _resourceService) :
		m_ResourceService(_resourceService) {
		
	}
	MarketService::~MarketService(void) {
		
	}

	void MarketService::sellCargo(const inf::ResourceBundle& _cargo) {
		m_ResourceService.payResourceBundle(_cargo);
	}

}