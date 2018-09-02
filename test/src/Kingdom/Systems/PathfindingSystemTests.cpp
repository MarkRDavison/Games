#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Kingdom/Systems/PathfindingSystem.hpp>
#include <Kingdom/Components/PathfindingComponent.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>
#include <Mocks/Kingdom/Services/PathfindingServiceMock.hpp>
#include <Mocks/Kingdom/Services/SurfaceServiceMock.hpp>
#include <Mocks/Kingdom/Services/PathSurfaceMock.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>

namespace kdm {
	namespace PathfindingSystemTests {
		
		TEST_CASE("Updating entity requesting pathfinding when a path cannot be found cancels the request and sets the failed flag", "[Kingdom][System][PathfindingSystem]") {
			PathSurfaceMock pathSurfaceMock;
			SurfaceServiceMock surfaceServiceMock;
			surfaceServiceMock.pathSurface = &pathSurfaceMock;
			PathfindingServiceMock pathfindingServiceMock;
			pathfindingServiceMock.path.isValid = false;
			PathfindingSystem system(pathfindingServiceMock, surfaceServiceMock);

			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity();
			PathfindingComponent& pc = e.addComponent<PathfindingComponent>();
			WaypointComponent& wc = e.addComponent<WaypointComponent>();

			pc.pathRequested = true;
			pc.start = { 0, 0 };
			pc.end = { 1, 0 };

			system.updateEntity(&e, 1.0f);

			REQUIRE_FALSE(pc.pathRequested);
			REQUIRE(pc.pathAttempedButFailed);
		}

		TEST_CASE("Updating entity requesting pathfinding when a path can be found cancels the request and sets the waypoint components waypoints", "[Kingdom][System][PathfindingSystem]") {
			PathNode start;
			start.x = 0;
			start.y = 0;
			start.nodeType = PathNode::NodeType::Start;
			PathNode middle;
			middle.x = 1;
			middle.y = 0;
			middle.nodeType = PathNode::NodeType::Standard;
			PathNode end;
			end.x = 2;
			end.y = 0;
			end.nodeType = PathNode::NodeType::End;

			PathSurfaceMock pathSurfaceMock;
			SurfaceServiceMock surfaceServiceMock;
			surfaceServiceMock.pathSurface = &pathSurfaceMock;
			PathfindingServiceMock pathfindingServiceMock;
			pathfindingServiceMock.path.isValid = true;
			pathfindingServiceMock.path.nodes = { start, middle, end };
			PathfindingSystem system(pathfindingServiceMock, surfaceServiceMock);

			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity();
			PathfindingComponent& pc = e.addComponent<PathfindingComponent>();
			WaypointComponent& wc = e.addComponent<WaypointComponent>();

			pc.pathRequested = true;
			pc.start = { 0, 0 };
			pc.end = { 1, 1 };

			system.updateEntity(&e, 1.0f);

			REQUIRE_FALSE(pc.pathRequested);
			REQUIRE_FALSE(pc.pathAttempedButFailed);
			REQUIRE(3 == wc.waypoints.size());
			REQUIRE(Definitions::TileSize / 2.0f + start.x == wc.waypoints[0].x);
			REQUIRE(Definitions::TileSize / 2.0f + start.y == wc.waypoints[0].y);
			REQUIRE(Definitions::TileSize / 2.0f + middle.x == wc.waypoints[1].x);
			REQUIRE(Definitions::TileSize / 2.0f + middle.y == wc.waypoints[1].y);
			REQUIRE(Definitions::TileSize / 2.0f + end.x == wc.waypoints[2].x);
			REQUIRE(Definitions::TileSize / 2.0f + end.y == wc.waypoints[2].y);
		}
	}
}
