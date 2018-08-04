#ifndef INCLUDED_HURRICANE_SYSTEMS_PLAYER_CONTROL_SYSTEM_HPP_
#define INCLUDED_HURRICANE_SYSTEMS_PLAYER_CONTROL_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace hur {
	
	class PlayerControlSystem : public ecs::System {
	public:
		PlayerControlSystem(inf::InputManager& _inputManager, inf::TextureManager& _textureManager);

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const;
		void createLaser(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const;

	private:
		inf::InputManager& m_InputManager;
		inf::TextureManager& m_TextureManager;
	};

}

#endif // INCLUDED_HURRICANE_SYSTEMS_PLAYER_CONTROL_SYSTEM_HPP_