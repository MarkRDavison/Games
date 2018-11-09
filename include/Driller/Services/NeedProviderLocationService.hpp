#ifndef INCLUDED_DRILLER_SERVICES_NEED_PROVIDER_LOCATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_NEED_PROVIDER_LOCATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/INeedProviderLocationService.hpp>
#include <Driller/DataStructures/BuildingData.hpp>

namespace drl {


	class NeedProviderLocationService : public INeedProviderLocationService {
	public:
		NeedProviderLocationService(const BuildingData& _buildingData);
		~NeedProviderLocationService(void) override;

		bool isNeedProviderAvailable(std::size_t _needId) const override;
		EntityId getNeedProvider(std::size_t _needId, const sf::Vector2f& _currentPosition) const override;

	private:
		const BuildingData& m_BuildingData;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_NEED_PROVIDER_LOCATION_SERVICE_HPP_