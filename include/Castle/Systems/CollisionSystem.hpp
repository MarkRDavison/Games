#ifndef INCLUDED_CASTLE_SYSTEMS_COLLISION_SYSTEM_HPP_
#define INCLUDED_CASTLE_SYSTEMS_COLLISION_SYSTEM_HPP_

#include <Castle/Systems/System.hpp>
#include <Castle/Infrastructure/EntityGroups.hpp>
#include <Castle/Components/PlayerComponent.hpp>
#include <Castle/Components/PositionComponent.hpp>
#include <Castle/Components/CollisionComponent.hpp>
#include <Castle/GameObjects/Level.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/EntityManager.hpp>

#include <Utility/Orientation.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <map>

namespace castle {
	class CollisionSystem : System {
	public:
		CollisionSystem(void);

		void update(float _delta, ecs::EntityManager& _entityManager, Level *_level);
		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta, Level *_level);

		void doHorizontal(float _delta, PositionComponent& pos, CollisionComponent& _collision, PlayerComponent& _player, Level *_level);
		void doVertical(float _delta, PositionComponent& pos, CollisionComponent& _collision, PlayerComponent& _player, Level *_level);

		void handleMovementStuff(float _delta, Level *_level);

		void handleCollisionComponentsCollide(ecs::Entity* _firstEntity, ecs::Entity* _secondEntity, float _delta);

		void updateHorizontalVelocityBasedOnIntersection(CollisionComponent& _collisionComponent, PositionComponent& _positionComponent, const sf::FloatRect& _intersectionObjectBounds, float _delta);
		void updateVerticalVelocityBasedOnIntersection(CollisionComponent& _collisionComponent, PositionComponent& _positionComponent, const sf::FloatRect& _intersectionObjectBounds, float _delta);

		bool detectCollisionAfterMovement(inf::Orientation _orientation, CollisionComponent& _collisionComponent, Level *_level) const;
		
		std::map<ecs::Entity *, std::vector<ecs::Entity * >> collidingDynamicBodies;
	};
}

#endif // INCLUDED_CASTLE_SYSTEMS_COLLISION_SYSTEM_HPP_