#ifndef INCLUDED_CASTLE_SCENES_PLAYER_COLLISION_TEST_SCENE_HPP_
#define INCLUDED_CASTLE_SCENES_PLAYER_COLLISION_TEST_SCENE_HPP_

#include <Castle/GameObjects/Level.hpp>

#include <Castle/Systems/CollisionSystem.hpp>
#include <Castle/Systems/KinematicSystem.hpp>
#include <Castle/Systems/PlayerControlSystem.hpp>
#include <Castle/Systems/PlayerInteractionSystem.hpp>
#include <Castle/Systems/WaypointSystem.hpp>

#include <Castle/Infrastructure/CastleConfigurationManager.hpp>
#include <Castle/Infrastructure/AutoPlayerInputManager.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/Scene.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace castle {

	class PlayerCollisionTestScene : public inf::Scene {
	public:
		PlayerCollisionTestScene(inf::TextureManager& _textureManager, AutoPlayerInputManager& _inputManager, CastleConfigurationManager& _castleConfigurationManager, ecs::EntityManager& _entityManager, CollisionSystem& _collisionSystem, KinematicSystem& _kinematicSystem, PlayerControlSystem& _playerControlSystem, PlayerInteractionSystem& _playerInteractionSystem, WaypointSystem& _waypointSystem);
		~PlayerCollisionTestScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

		void initializeTestScene1(void);

		CastleConfigurationManager& m_CastleConfigurationManager;
		ecs::EntityManager& m_EntityManager;
		AutoPlayerInputManager& m_InputManager;
		inf::TextureManager& m_TextureManager;

		Level *m_Level;
		CollisionSystem& m_CollisionSystem;
		KinematicSystem& m_KinematicSystem;
		PlayerControlSystem& m_PlayerControlSystem;
		PlayerInteractionSystem& m_PlayerInteractionSystem;
		WaypointSystem& m_WaypointSystem;
	};

}

#endif // INCLUDED_CASTLE_SCENES_PLAYER_COLLISION_TEST_SCENE_HPP_