#ifndef INCLUDED_CASTLE_SYSTEMS_PLAYER_INTERACTION_SYSTEM_HPP_
#define INCLUDED_CASTLE_SYSTEMS_PLAYER_INTERACTION_SYSTEM_HPP_

#include <Castle/Systems/System.hpp>

namespace castle {
	class PlayerInteractionSystem : System {
	public:
		PlayerInteractionSystem(void);

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager) const;

		void createPlayerInteractionOutlineEntity(const sf::Vector2f& _position, const sf::Vector2f& _size, float _duration, ecs::EntityManager& _entityManager) const;
	};
}

#endif // INCLUDED_CASTLE_SYSTEMS_PLAYER_INTERACTION_SYSTEM_HPP_