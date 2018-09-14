#ifndef INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_TOWER_PLACEABLE_SURFACE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_TOWER_PLACEABLE_SURFACE_SERVICE_MOCK_HPP_

#include <Intrusion/Services/ITowerPlaceableSurfaceService.hpp>

namespace itr {
	
	class TowerPlaceableSurfaceServiceMock : public ITowerPlaceableSurfaceService {
	public:
		~TowerPlaceableSurfaceServiceMock(void) override = default;

		void setActiveSurface(ITowerPlaceableSurface *_surface) override {
			surface = _surface;
		}
		ITowerPlaceableSurface *getActiveSurface(void) const override {
			return surface;
		}

		ITowerPlaceableSurface *surface{ nullptr };
	};

}

#endif // INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_TOWER_PLACEABLE_SURFACE_SERVICE_MOCK_HPP_