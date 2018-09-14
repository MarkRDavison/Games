#include <Intrusion/Services/TowerPlaceableSurfaceService.hpp>

namespace itr {

	TowerPlaceableSurfaceService::TowerPlaceableSurfaceService(void) {
		
	}
	TowerPlaceableSurfaceService::~TowerPlaceableSurfaceService(void) {
		
	}

	void TowerPlaceableSurfaceService::setActiveSurface(ITowerPlaceableSurface *_surface) {
		m_ActiveSurface = _surface;
	}
	ITowerPlaceableSurface *TowerPlaceableSurfaceService::getActiveSurface(void) const {
		return m_ActiveSurface;
	}
}