#ifndef INCLUDED_INFRASTRUCTURE_SERVICES_PATH_FINDING_SERVICE_HPP_
#define INCLUDED_INFRASTRUCTURE_SERVICES_PATH_FINDING_SERVICE_HPP_

#include <Infrastructure/Services/IPathSurface.hpp>
#include <Infrastructure/Services/IPathfindingService.hpp>
#include <Infrastructure/DataStructures/Path.hpp>
#include <limits>

namespace inf {

	class PathfindingService : public IPathfindingService {
	private:
		static const int Infinity{ std::numeric_limits<int>::max() };
		struct InternalPathNode {
			int x;
			int y;
			int cost{ Infinity };
			bool open{ false };
			bool closed{ false };
			int g{0};
			int h{0};
			bool end{ false };
			bool start{ false };
			bool canTraverse{ true };
			InternalPathNode *parent{ nullptr };
		};

		int calculateH(int _xCurrent, int _yCurrent, int _xEnd, int _yEnd) const;
		int calculateG(int _xStart, int _yStart, int _xCurrent, int _yCurrent) const;	

	public:
		Path findPath(int _xStart, int _yStart, int _xEnd, int _yEnd, const IPathSurface& _pathSurface) const override;

	};

}

#endif // INCLUDED_INFRASTRUCTURE_SERVICES_PATH_FINDING_SERVICE_HPP_