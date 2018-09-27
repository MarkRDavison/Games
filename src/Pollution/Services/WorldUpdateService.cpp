#include <Pollution/Services/WorldUpdateService.hpp>

namespace pol {

	WorldUpdateService::WorldUpdateService(inf::IResourceService& _resourceService) :
		m_ResourceService(_resourceService) {
		
	}

	WorldUpdateService::~WorldUpdateService(void) {
		
	}

	void WorldUpdateService::update(float _delta, WorldData& _worldData) {
		_worldData.rotation += _worldData.rotationRate * _delta;
		if (_worldData.rotation >= 360.0f) {
			_worldData.rotation -= 360.0f;
		} else if (_worldData.rotation < 0.0f) {
			_worldData.rotation += 360.0f;
		}

		for (BuildingData& building : _worldData.buildings) {
			if (building.active) {
				building.accumulatedAnimationTime += _delta;
				building.accumulatedDropTime += _delta;
				if (building.accumulatedDropTime >= building.dropRate) {
					building.accumulatedDropTime -= building.dropRate;
					m_ResourceService.receiveResourceBundle(building.drops);
				}
			}
		}
	}

}
