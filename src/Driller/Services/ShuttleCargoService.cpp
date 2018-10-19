#include <Driller/Services/ShuttleCargoService.hpp>

namespace drl {
	
	ShuttleCargoService::ShuttleCargoService(inf::IResourceService& _resourceService) :
		m_ResourceService(_resourceService) {
		
	}
	ShuttleCargoService::~ShuttleCargoService(void) {
		
	}

	void ShuttleCargoService::loadShuttleWithCargo(ShuttleInstance& _shuttle) {
		const int oreAvailable = m_ResourceService.getResource(Definitions::OreResourceName);
		if (oreAvailable > 0) {
			m_ResourceService.updateResource(Definitions::OreResourceName, -oreAvailable);

			_shuttle.cargo.resources.emplace_back(Definitions::OreResourceName, oreAvailable);
		}
	}

}