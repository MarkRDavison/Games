#ifndef INCLUDED_INFRASTRUCTURE_SERVICES_IPATH_FINDING_SERVICE_HPP_
#define INCLUDED_INFRASTRUCTURE_SERVICES_IPATH_FINDING_SERVICE_HPP_

#include <Infrastructure/Services/IPathSurface.hpp>
#include <Infrastructure/DataStructures/Path.hpp>

namespace inf {

	class IPathfindingService {
	public:
		virtual ~IPathfindingService() = default;
		virtual Path findPath(int _xStart, int _yStart, int _xEnd, int _yEnd, const IPathSurface& _pathSurface) const = 0;
	};

}

#endif // INCLUDED_INFRASTRUCTURE_SERVICES_IPATH_FINDING_SERVICE_HPP_