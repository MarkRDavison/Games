#ifndef INCLUDED_MOCKS_KINGDOM_SERVICES_PATH_SURFACE_MOCK_HPP_
#define INCLUDED_MOCKS_KINGDOM_SERVICES_PATH_SURFACE_MOCK_HPP_

#include <Kingdom/Services/IPathSurface.hpp>
#include <functional>

namespace kdm {
	
	class PathSurfaceMock : public IPathSurface {
	public:
		~PathSurfaceMock(void) override {}
		unsigned getWidth(void) const noexcept override { return width; }
		unsigned getHeight(void) const noexcept override { return height; }
		bool canTraverse(const sf::Vector2u& _coordinates) const override {
			if (canTraverseCallback) {
				return canTraverseCallback(_coordinates);
			}

			return true;
		}
		std::vector<sf::Vector2u> getValidNeighbours(const sf::Vector2u& _coordinates) const override {
			if (getValidNeighboursCallback) {
				return getValidNeighboursCallback(_coordinates);
			}
			return {};
		}

		std::string getSurfaceName(void) const override {
			return name;
		}

		int width{0};
		int height{0};
		std::string name;
		std::function<std::vector<sf::Vector2u>(const sf::Vector2u&)> getValidNeighboursCallback;
		std::function<bool(const sf::Vector2u&)> canTraverseCallback;
	};

}

#endif // INCLUDED_MOCKS_KINGDOM_SERVICES_PATH_SURFACE_MOCK_HPP_