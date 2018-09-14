#ifndef INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_TOWER_PLACEABLE_SURFACE_MOCK_HPP_
#define INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_TOWER_PLACEABLE_SURFACE_MOCK_HPP_

#include <Intrusion/Infrastructure/Interfaces/ITowerPlaceableSurface.hpp>

namespace itr {
	
	class TowerPlaceableSurfaceMock : public ITowerPlaceableSurface {
	public:
		~TowerPlaceableSurfaceMock(void) override = default;

		unsigned getWidth(void) const noexcept override { return width; }
		unsigned getHeight(void) const noexcept override { return height; }

		bool canPlacePrototype(const sf::Vector2i& _coordinates, const ParsedTower& _prototype) const override {
			return canPlace;
		}

		unsigned width{ 0 };
		unsigned height{ 0 };
		bool canPlace{ false };
	};

}

#endif // INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_TOWER_PLACEABLE_SURFACE_MOCK_HPP_