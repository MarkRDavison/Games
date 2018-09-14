#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_SERVICES_INTERFACES_I_TOWER_PLACEABLE_SURFACE_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_SERVICES_INTERFACES_I_TOWER_PLACEABLE_SURFACE_HPP_
#include <Intrusion/DataStructures/ParsedTower.hpp>

namespace itr {
	
	class ITowerPlaceableSurface {
	public:
		virtual ~ITowerPlaceableSurface(void) = default;

		virtual unsigned getWidth(void) const noexcept = 0;
		virtual unsigned getHeight(void) const noexcept = 0;

		virtual bool canPlacePrototype(const sf::Vector2i& _coordinates, const ParsedTower& _prototype) const = 0;
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_SERVICES_INTERFACES_I_TOWER_PLACEABLE_SURFACE_HPP_