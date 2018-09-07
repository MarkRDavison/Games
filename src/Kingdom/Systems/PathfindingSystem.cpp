#include <Kingdom/Systems/PathfindingSystem.hpp>
#include <Kingdom/Infrastructure/KingdomEntityGroups.hpp>
#include <Kingdom/Components/PathfindingComponent.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>

namespace kdm {

	PathfindingSystem::PathfindingSystem(const inf::IPathfindingService& _pathfindingService, const inf::ISurfaceService& _surfaceService) :
		m_PathfindingService(_pathfindingService),
		m_SurfaceService(_surfaceService) {
		
	}
	PathfindingSystem::~PathfindingSystem(void) {
		
	}

	void PathfindingSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(EntityGroup::GPathfindable)) {
			updateEntity(e, _delta);
		}
	}

	void PathfindingSystem::updateEntity(ecs::Entity *_entity, float _delta) {
		PathfindingComponent& pc = _entity->getComponent<PathfindingComponent>();
		WaypointComponent& wc = _entity->getComponent<WaypointComponent>();

		if (!pc.pathRequested) {
			return;
		}

		pc.pathRequested = false;
		const inf::Path& p = m_PathfindingService.findPath(pc.start.x, pc.start.y, pc.end.x, pc.end.y, m_SurfaceService.getCurrentSurface());

		if (!p.isValid) {
			pc.pathAttempedButFailed = true;
			return;
		}

		wc.waypoints.clear();
		wc.currentWaypointIndex = 0;
		for (const inf::PathNode& node : p.nodes) {
			wc.waypoints.emplace_back(convertTileCoordToWaypointCoord(node.x, node.y));
		}
	}

	sf::Vector2f PathfindingSystem::convertTileCoordToWaypointCoord(int _x, int _y) {
		return sf::Vector2f(static_cast<float>(_x), static_cast<float>(_y)) * Definitions::TileSize + sf::Vector2f(Definitions::TileSize / 2.0f, Definitions::TileSize / 2.0f);
	}
}
