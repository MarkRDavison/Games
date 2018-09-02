#include <Kingdom/Services/SurfaceService.hpp>
#include <Kingdom/Exceptions/SurfaceNotFoundException.hpp>
#include <algorithm>

namespace kdm {
	SurfaceService::SurfaceService(void) {
		
	}
	SurfaceService::~SurfaceService(void) {
		
	}


	IPathSurface& SurfaceService::getCurrentSurface(void) const {
		if (m_CurrentSurface == nullptr) {
			throw SurfaceNotFoundException("Current");
		}

		return *m_CurrentSurface;
	}

	void SurfaceService::addSurface(IPathSurface *_surface) {
		m_Surfaces.push_back(_surface);
	}
	void SurfaceService::removeSurface(const std::string& _surfaceName) {
		if (m_CurrentSurface != nullptr && _surfaceName == m_CurrentSurface->getSurfaceName()) {
			m_CurrentSurface = nullptr;
		}
		m_Surfaces.erase(std::find_if(m_Surfaces.begin(), m_Surfaces.end(), [_surfaceName](const IPathSurface* _surface) { return _surface->getSurfaceName() == _surfaceName; }));
	}
	void SurfaceService::setCurrentSurface(const std::string& _surfaceName) {
		const auto result = std::find_if(m_Surfaces.begin(), m_Surfaces.end(), [_surfaceName](const IPathSurface* _surface) { return _surface->getSurfaceName() == _surfaceName; });

		if (result != m_Surfaces.end()) {
			m_CurrentSurface = *result;
		}
	}
}
