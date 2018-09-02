#ifndef INCLUDED_PACMAN_SCENES_GAME_SCENE_HPP_
#define INCLUDED_PACMAN_SCENES_GAME_SCENE_HPP_

#include <Pacman/GameObjects/Board.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace pacman {
	enum class GhostType;

	enum PacmanGroup : std::size_t {
		GPac,
		GPickup,
		GGhost
	};

	class GameScene : public inf::Scene {
	public:
		GameScene(inf::TextureManager& _textureManager, Board *_board);
		~GameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

		void initialize(void);

		void createPacman(const sf::Vector2f& _position);
		void createGhost(const sf::Vector2f& _position, GhostType _type);

		ecs::EntityManager m_EntityManager;

		inf::TextureManager& m_TextureManager;
		Board *m_Board;
	};
}

#endif // INCLUDED_PACMAN_SCENES_GAME_SCENE_HPP_