#ifndef INCLUDED_KINGDOM_SYSTEMS_PATHFINDING_SYSTEM_HPP_
#define INCLUDED_KINGDOM_SYSTEMS_PATHFINDING_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>
#include <Infrastructure/Services/IPathfindingService.hpp>
#include <Infrastructure/Services/ISurfaceService.hpp>

namespace kdm {

	class PathfindingSystem : public ecs::System {
	public:
		PathfindingSystem(const inf::IPathfindingService& _pathfindingService, const inf::ISurfaceService& _surfaceService);
		~PathfindingSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		void updateEntity(ecs::Entity* _entity, float _delta);

		static sf::Vector2f convertTileCoordToWaypointCoord(int _x, int _y);

	private:
		const inf::IPathfindingService& m_PathfindingService;
		const inf::ISurfaceService& m_SurfaceService;
	};

}

#endif // INCLUDED_KINGDOM_SYSTEMS_PATHFINDING_SYSTEM_HPP_