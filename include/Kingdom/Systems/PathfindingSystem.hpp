#ifndef INCLUDED_KINGDOM_SYSTEMS_PATHFINDING_SYSTEM_HPP_
#define INCLUDED_KINGDOM_SYSTEMS_PATHFINDING_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>
#include <Kingdom/Services/IPathfindingService.hpp>
#include <Kingdom/Services/ISurfaceService.hpp>

namespace kdm {

	class PathfindingSystem : public ecs::System {
	public:
		PathfindingSystem(const IPathfindingService& _pathfindingService, const ISurfaceService& _surfaceService);
		~PathfindingSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		void updateEntity(ecs::Entity* _entity, float _delta);

		static sf::Vector2f convertTileCoordToWaypointCoord(int _x, int _y);

	private:
		const IPathfindingService& m_PathfindingService;
		const ISurfaceService& m_SurfaceService;
	};

}

#endif // INCLUDED_KINGDOM_SYSTEMS_PATHFINDING_SYSTEM_HPP_