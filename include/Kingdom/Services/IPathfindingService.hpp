#ifndef INCLUDED_KINGDOM_SERVICES_IPATH_FINDING_SERVICE_HPP_
#define INCLUDED_KINGDOM_SERVICES_IPATH_FINDING_SERVICE_HPP_

#include <Kingdom/Services/IPathSurface.hpp>
#include <Kingdom/DataStructures/Path.hpp>

namespace kdm {

	class IPathfindingService {
	public:
		virtual ~IPathfindingService() = default;
		virtual Path findPath(int _xStart, int _yStart, int _xEnd, int _yEnd, const IPathSurface& _pathSurface) const = 0;
	};

}

#endif // INCLUDED_KINGDOM_SERVICES_IPATH_FINDING_SERVICE_HPP_