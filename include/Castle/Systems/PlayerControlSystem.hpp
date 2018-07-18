#ifndef INCLUDED_CASTLE_SYSTEMS_PLAYER_CONTROL_SYSTEM_HPP_
#define INCLUDED_CASTLE_SYSTEMS_PLAYER_CONTROL_SYSTEM_HPP_

#include <Castle/Systems/System.hpp>
#include <Castle/Infrastructure/EntityGroups.hpp>
#include <Infrastructure/InputManager.hpp>

namespace castle {
	class PlayerControlSystem : System {
	public:
		PlayerControlSystem(EntityGroup _group, inf::InputManager& _inputManager);

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta) const;

		EntityGroup m_Group;
		inf::InputManager& m_InputManager;
	};
}

#endif // INCLUDED_CASTLE_SYSTEMS_PLAYER_CONTROL_SYSTEM_HPP_