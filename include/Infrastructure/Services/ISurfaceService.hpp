#ifndef INCLUDE_INFRASTRUCTURE_SERVICES_ISURFACE_SERVICE_HPP_
#define INCLUDE_INFRASTRUCTURE_SERVICES_ISURFACE_SERVICE_HPP_

#include <Infrastructure/Services/IPathSurface.hpp>

namespace inf {
	
	class ISurfaceService {
	public:
		virtual ~ISurfaceService(void) = default;

		virtual IPathSurface& getCurrentSurface(void) const = 0;
	};

}

#endif // INCLUDE_INFRASTRUCTURE_SERVICES_ISURFACE_SERVICE_HPP_