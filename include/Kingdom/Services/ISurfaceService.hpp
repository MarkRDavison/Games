#ifndef INCLUDE_KINGDOM_SERVICES_ISURFACE_SERVICE_HPP_
#define INCLUDE_KINGDOM_SERVICES_ISURFACE_SERVICE_HPP_

#include <Kingdom/Services/IPathSurface.hpp>

namespace kdm {
	
	class ISurfaceService {
	public:
		virtual ~ISurfaceService(void) = default;

		virtual IPathSurface& getCurrentSurface(void) const = 0;
	};

}

#endif // INCLUDE_KINGDOM_SERVICES_ISURFACE_SERVICE_HPP_