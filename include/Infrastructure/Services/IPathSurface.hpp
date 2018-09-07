#ifndef INCLUDED_INFRASTRUCTURE_SERVICES_I_PATH_SURFACE_HPP_
#define INCLUDED_INFRASTRUCTURE_SERVICES_I_PATH_SURFACE_HPP_

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

namespace inf {

	class IPathSurface {
	public:
		virtual ~IPathSurface() = default;

		virtual unsigned getWidth(void) const noexcept = 0;
		virtual unsigned getHeight(void) const noexcept = 0;
		virtual bool canTraverse(const sf::Vector2u& _coordinates) const = 0;
		virtual std::string getSurfaceName(void) const = 0;

		virtual std::vector<sf::Vector2u> getValidNeighbours(const sf::Vector2u& _coordinates) const = 0;

	};
	
}

#endif // INCLUDED_INFRASTRUCTURE_SERVICES_I_PATH_SURFACE_HPP_