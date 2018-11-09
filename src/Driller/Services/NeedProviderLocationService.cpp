#include <Driller/Services/NeedProviderLocationService.hpp>
#include <stdexcept>

namespace drl {

	NeedProviderLocationService::NeedProviderLocationService(const BuildingData& _buildingData) :
		m_BuildingData(_buildingData) {
		
	}

	NeedProviderLocationService::~NeedProviderLocationService(void) {

	}

	bool NeedProviderLocationService::isNeedProviderAvailable(std::size_t _needId) const {
		for (const BuildingInstance& building : m_BuildingData.buildings) {
			if (building.providesNeeds && building.providedNeedId == _needId) {
				for (const BuildingProvidedNeed& providedNeed : building.providedNeeds) {
					if (providedNeed.allocatedWorkerId == 0u) {
						return true;
					}
				}
			}
		}

		return false;
	}
	EntityId NeedProviderLocationService::getNeedProvider(std::size_t _needId, const sf::Vector2f& _currentPosition) const {
		for (const BuildingInstance& building : m_BuildingData.buildings) {
			if (building.providesNeeds && building.providedNeedId == _needId) {
				for (const BuildingProvidedNeed& providedNeed : building.providedNeeds) {
					if (providedNeed.allocatedWorkerId == 0u) {
						return building.Id;
					}
				}
			}
		}

		return 0u;
	}

}
