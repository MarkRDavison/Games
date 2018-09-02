#ifndef INCLUDED_MOCKS_KINGDOM_SERVICES_PATHFINDING_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_KINGDOM_SERVICES_PATHFINDING_SERVICE_MOCK_HPP_

#include <Kingdom/Services/IPathfindingService.hpp>

namespace kdm {
	class PathfindingServiceMock : public IPathfindingService {
	public:
		Path findPath(int _xStart, int _yStart, int _xEnd, int _yEnd, const IPathSurface& _pathSurface) const override {
			return path;
		}
		
		Path path{};
	};
}

#endif // INCLUDED_MOCKS_KINGDOM_SERVICES_PATHFINDING_SERVICE_MOCK_HPP_

