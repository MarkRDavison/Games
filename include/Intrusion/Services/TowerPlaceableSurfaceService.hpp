#ifndef INCLUDED_INTRUSION_SERVICES_TOWER_PLACEABLE_SURFACE_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_TOWER_PLACEABLE_SURFACE_SERVICE_HPP_

#include <Intrusion/Services/ITowerPlaceableSurfaceService.hpp>

namespace itr {
	
	class TowerPlaceableSurfaceService : public ITowerPlaceableSurfaceService {
	public:
		TowerPlaceableSurfaceService(void);
		~TowerPlaceableSurfaceService(void) override;

		void setActiveSurface(ITowerPlaceableSurface *_surface) override;
		ITowerPlaceableSurface *getActiveSurface(void) const override;

	private:
		ITowerPlaceableSurface *m_ActiveSurface{ nullptr };
	};

}

#endif // INCLUDED_INTRUSION_SERVICES_TOWER_PLACEABLE_SURFACE_SERVICE_HPP_