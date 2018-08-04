#ifndef INCLUDED_HURRICANE_SCENES_GAME_SCENE_HPP_
#define INCLUDED_HURRICANE_SCENES_GAME_SCENE_HPP_

#include <Hurricane/Objects/Level.hpp>

#include <Hurricane/Systems/CollisionSystem.hpp>
#include <Hurricane/Systems/KinematicSystem.hpp>
#include <Hurricane/Systems/PlayerControlSystem.hpp>
#include <Hurricane/Systems/ProjectileControlSystem.hpp>

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace hur {
	class GameScene : public inf::Scene {
	public:
		GameScene(inf::TextureManager& _textureManager, CollisionSystem& _collisionSystem, KinematicSystem& _kinematicSystem, PlayerControlSystem& _playerControlSystem, ProjectileControlSystem& _projectileControlSystem);
		~GameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		void addPlayer(void);
		void addEnemy(int _index, const sf::Vector2f& _position);

		Level *m_Level;

		inf::TextureManager& m_TextureManager;
		CollisionSystem& m_CollisionSystem;
		KinematicSystem& m_KinematicSystem;
		PlayerControlSystem& m_PlayerControlSystem;
		ProjectileControlSystem& m_ProjectileControlSystem;
	};
}

#endif // INCLUDED_HURRICANE_SCENES_GAME_SCENE_HPP_