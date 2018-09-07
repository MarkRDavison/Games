#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Infrastructure/Services/PathfindingService.hpp>
#include <Mocks/Infrastructure/Services/PathSurfaceMock.hpp>

namespace inf {
	namespace PathfindingServiceTests {

		void validateStart(const Path& _path, unsigned _index, const sf::Vector2u& _coordinates) {
			REQUIRE(_coordinates.x == _path.nodes[_index].x);
			REQUIRE(_coordinates.y == _path.nodes[_index].y);
			REQUIRE(PathNode::NodeType::Start == _path.nodes[_index].nodeType);
		}
		void validateNode(const Path& _path, unsigned _index, const sf::Vector2u& _coordinates) {
			REQUIRE(_coordinates.x == _path.nodes[_index].x);
			REQUIRE(_coordinates.y == _path.nodes[_index].y);
			REQUIRE(PathNode::NodeType::Standard == _path.nodes[_index].nodeType);
		}
		void validateEnd(const Path& _path, unsigned _index, const sf::Vector2u& _coordinates) {
			REQUIRE(_coordinates.x == _path.nodes[_index].x);
			REQUIRE(_coordinates.y == _path.nodes[_index].y);
			REQUIRE(PathNode::NodeType::End == _path.nodes[_index].nodeType);
		}

		TEST_CASE("Pathfinding service returns correct path when end is next to start", "[Services][PathFindingService]") {
			PathfindingService pfs;

			PathSurfaceMock pathSurface;
			pathSurface.width = 5;
			pathSurface.height = 4;
			pathSurface.canTraverseCallback = [](const sf::Vector2u& _coordinates) {
				return true;
			};
			pathSurface.getValidNeighboursCallback = [pathSurface](const sf::Vector2u& _coordinates) {
				std::vector<sf::Vector2u> neighbours{};

				if (_coordinates.x > 0) {
					// left
					neighbours.push_back(sf::Vector2u(_coordinates.x - 1, _coordinates.y));
				}
				if (_coordinates.y > 0) {
					// top
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y - 1));
				}
				if (_coordinates.x < pathSurface.getWidth() - 1) {
					// right
					neighbours.push_back(sf::Vector2u(_coordinates.x + 1, _coordinates.y));
				}
				if (_coordinates.y < pathSurface.getHeight() - 1) {
					// bottom
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y + 1));
				}

				return neighbours;
			};

			auto path = pfs.findPath(0, 0, 1, 0, pathSurface);

			REQUIRE(2 == path.nodes.size());
			REQUIRE(path.isValid);

			validateStart(path, 0, { 0, 0 });
			validateEnd(path, 1, { 1, 0 });
		}

		TEST_CASE("Pathfinding service returns correct path along a 1 x 5 desired path", "[Services][PathFindingService]") {
			PathfindingService pfs;

			PathSurfaceMock pathSurface;
			pathSurface.width = 5;
			pathSurface.height = 1;
			pathSurface.canTraverseCallback = [](const sf::Vector2u& _coordinates) {
				return true;
			};
			pathSurface.getValidNeighboursCallback = [pathSurface](const sf::Vector2u& _coordinates) {
				std::vector<sf::Vector2u> neighbours{};

				if (_coordinates.x > 0) {
					// left
					neighbours.push_back(sf::Vector2u(_coordinates.x - 1, _coordinates.y));
				}
				if (_coordinates.y > 0) {
					// top
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y - 1));
				}
				if (_coordinates.x < pathSurface.getWidth() - 1) {
					// right
					neighbours.push_back(sf::Vector2u(_coordinates.x + 1, _coordinates.y));
				}
				if (_coordinates.y < pathSurface.getHeight() - 1) {
					// bottom
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y + 1));
				}

				return neighbours;
			};

			auto path = pfs.findPath(0, 0, 4, 0, pathSurface);

			REQUIRE(5 == path.nodes.size());
			REQUIRE(path.isValid);

			validateStart(path, 0, { 0, 0 });

			validateNode(path, 1, { 1, 0 });
			validateNode(path, 2, { 2, 0 });
			validateNode(path, 3, { 3, 0 });

			validateEnd(path, 4, { 4, 0 });
		}

		TEST_CASE("Pathfinding service returns correct path along a 2 x 5 desired path with a slight detour", "[Services][PathFindingService]") {
			PathfindingService pfs;

			PathSurfaceMock pathSurface;
			pathSurface.width = 5;
			pathSurface.height = 2;
			pathSurface.canTraverseCallback = [](const sf::Vector2u& _coordinates) {
				return _coordinates != sf::Vector2u(2, 0) && _coordinates != sf::Vector2u(4, 1) && _coordinates != sf::Vector2u(0, 1);
			};
			pathSurface.getValidNeighboursCallback = [pathSurface](const sf::Vector2u& _coordinates) {
				std::vector<sf::Vector2u> neighbours{};

				if (_coordinates.x > 0) {
					// left
					neighbours.push_back(sf::Vector2u(_coordinates.x - 1, _coordinates.y));
				}
				if (_coordinates.y > 0) {
					// top
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y - 1));
				}
				if (_coordinates.x < pathSurface.getWidth() - 1) {
					// right
					neighbours.push_back(sf::Vector2u(_coordinates.x + 1, _coordinates.y));
				}
				if (_coordinates.y < pathSurface.getHeight() - 1) {
					// bottom
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y + 1));
				}

				return neighbours;
			};

			auto path = pfs.findPath(0, 0, 4, 0, pathSurface);

			REQUIRE(7 == path.nodes.size());
			REQUIRE(path.isValid);

			validateStart(path, 0, { 0, 0 });

			validateNode(path, 1, { 1, 0 });
			validateNode(path, 2, { 1, 1 });
			validateNode(path, 3, { 2, 1 });
			validateNode(path, 4, { 3, 1 });
			validateNode(path, 5, { 3, 0 });

			validateEnd(path, 6, { 4, 0 });
		}

		TEST_CASE("Ending on a non traversable tile cannot occur", "[Services][PathFindingService]") {
			PathfindingService pfs;

			PathSurfaceMock pathSurface;
			pathSurface.width = 5;
			pathSurface.height = 2;
			pathSurface.canTraverseCallback = [](const sf::Vector2u& _coordinates) {
				return _coordinates != sf::Vector2u(1, 0);
			};
			pathSurface.getValidNeighboursCallback = [pathSurface](const sf::Vector2u& _coordinates) {
				std::vector<sf::Vector2u> neighbours{};

				if (_coordinates.x > 0) {
					// left
					neighbours.push_back(sf::Vector2u(_coordinates.x - 1, _coordinates.y));
				}
				if (_coordinates.y > 0) {
					// top
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y - 1));
				}
				if (_coordinates.x < pathSurface.getWidth() - 1) {
					// right
					neighbours.push_back(sf::Vector2u(_coordinates.x + 1, _coordinates.y));
				}
				if (_coordinates.y < pathSurface.getHeight() - 1) {
					// bottom
					neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y + 1));
				}

				return neighbours;
			};

			auto path = pfs.findPath(0, 0, 1, 0, pathSurface);

			REQUIRE_FALSE(path.isValid);
		}
	}
}
