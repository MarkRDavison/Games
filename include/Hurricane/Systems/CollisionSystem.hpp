#ifndef INCLUDED_HURRICANE_SYSTEMS_COLLISION_SYSTEM_HPP_
#define INCLUDED_HURRICANE_SYSTEMS_COLLISION_SYSTEM_HPP_

#include <Hurricane/Infrastructure/EntityFactory.hpp>

#include <EntityComponentSystem/System.hpp>

namespace hur {

	class CollisionSystem : public ecs::System {
	public:
		CollisionSystem(EntityFactory& _entityFactory);

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void handleCollision(ecs::Entity* _entity1, ecs::Entity* _entity2, float _delta, ecs::EntityManager& _entityManager);
		void handleDamaging(ecs::Entity* _entity1, ecs::Entity* _entity2, ecs::EntityManager& _entityManager);
		void handlePickup(ecs::Entity* _player, ecs::Entity* _pickup, const ecs::EntityManager& _entityManager);

	private:
		EntityFactory& m_EntityFactory;
	};
	
}

#endif // INCLUDED_HURRICANE_SYSTEMS_COLLISION_SYSTEM_HPP_