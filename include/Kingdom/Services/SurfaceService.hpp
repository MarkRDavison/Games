#ifndef INCLUDED_KINGDOM_SERVICES_SURFACE_SERVICE_HPP_
#define INCLUDED_KINGDOM_SERVICES_SURFACE_SERVICE_HPP_

#include <Kingdom/Services/ISurfaceService.hpp>

namespace kdm {
	
	class SurfaceService : public ISurfaceService {
	public:
		SurfaceService(void);
		~SurfaceService(void) override;

		IPathSurface& getCurrentSurface(void) const override;

		void addSurface(IPathSurface *_surface);
		void removeSurface(const std::string& _surfaceName);
		void setCurrentSurface(const std::string& _surfaceName);


	private:
		std::vector<IPathSurface *> m_Surfaces;
		IPathSurface *m_CurrentSurface{nullptr};
	};

}

#endif // INCLUDED_KINGDOM_SERVICES_SURFACE_SERVICE_HPP_