#ifndef INCLUDED_MOCKS_KINGDOM_SERVICES_SURFACE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_KINGDOM_SERVICES_SURFACE_SERVICE_MOCK_HPP_

#include <Kingdom/Services/ISurfaceService.hpp>
#include <functional>

namespace kdm {
	
	class SurfaceServiceMock : public ISurfaceService {
	public:
		~SurfaceServiceMock(void) override {}

		IPathSurface& getCurrentSurface(void) const override {
			return *pathSurface;
		}

		IPathSurface *pathSurface;
	};

}

#endif // INCLUDED_MOCKS_KINGDOM_SERVICES_SURFACE_SERVICE_MOCK_HPP_