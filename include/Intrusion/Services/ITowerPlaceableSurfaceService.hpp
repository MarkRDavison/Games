#ifndef INCLUDED_INTRUSION_SERVICES_I_TOWER_PLACEABLE_SURFACE_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_I_TOWER_PLACEABLE_SURFACE_SERVICE_HPP_

#include <Intrusion/Infrastructure/Interfaces/ITowerPlaceableSurface.hpp>

namespace itr {
	
	class ITowerPlaceableSurfaceService {
	public:
		virtual ~ITowerPlaceableSurfaceService(void) = default;

		virtual void setActiveSurface(ITowerPlaceableSurface *_surface) = 0;
		virtual ITowerPlaceableSurface *getActiveSurface(void) const = 0;
	};

}

#endif // INCLUDED_INTRUSION_SERVICES_I_TOWER_PLACEABLE_SURFACE_SERVICE_HPP_