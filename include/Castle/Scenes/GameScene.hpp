#ifndef INCLUDED_CASTLE_SCENES_GAME_SCENE_HPP_
#define INCLUDED_CASTLE_SCENES_GAME_SCENE_HPP_

#include <Castle/GameObjects/Level.hpp>
#include <Castle/DataStructures/ParsedLevel.hpp>
#include <Castle/Systems/CollisionSystem.hpp>
#include <Castle/Systems/KinematicSystem.hpp>
#include <Castle/Systems/PlayerControlSystem.hpp>
#include <Castle/Systems/PlayerInteractionSystem.hpp>
#include <Castle/Systems/WaypointSystem.hpp>

#include <Castle/Infrastructure/CastleConfigurationManager.hpp>
#include <Castle/Infrastructure/EntityPrototypeFactory.hpp>
#include <Castle/Infrastructure/LevelTransitionCoordinator.hpp>

#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/Scene.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace castle {
	class GameScene : public inf::Scene {
	public:
		GameScene(inf::TextureManager& _textureManager, inf::InputManager& _inputManager, CastleConfigurationManager& _castleConfigurationManager, CollisionSystem& _collisionSystem, KinematicSystem& _kinematicSystem, PlayerControlSystem& _playerControlSystem, PlayerInteractionSystem& _playerInteractionSystem, WaypointSystem& _waypointSystem, EntityPrototypeFactory& _entityPrototypeFactory, LevelTransitionCoordinator& _levelTransitionCoordinator);
		~GameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		void initialize(Level *_level);
		void addPlayer(void) const;

		void setActiveLevel(const std::string& _levelName);

		CastleConfigurationManager& m_CastleConfigurationManager;
		inf::InputManager& m_InputManager;
		inf::TextureManager& m_TextureManager;

		Level *m_ActiveLevel;
		std::vector<Level *> m_Levels;
		std::vector<ParsedLevel> m_ParsedLevels;
		CollisionSystem& m_CollisionSystem;
		KinematicSystem& m_KinematicSystem;
		PlayerControlSystem& m_PlayerControlSystem;
		PlayerInteractionSystem& m_PlayerInteractionSystem;
		WaypointSystem& m_WaypointSystem;
		EntityPrototypeFactory& m_EntityPrototypeFactory;
		LevelTransitionCoordinator& m_LevelTransitionCoordinator;
	};
}

#endif // INCLUDED_CASTLE_SCENES_GAME_SCENE_HPP_