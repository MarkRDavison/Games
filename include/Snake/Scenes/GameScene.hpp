#ifndef INCLUDED_SNAKE_SCENES_GAME_SCENE_HPP_
#define INCLUDED_SNAKE_SCENES_GAME_SCENE_HPP_

#include <Snake/Infrastructure/SnakeConfigurationManager.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/EntityManager.hpp>

#include <Utility/Orientation.hpp>

#include <Infrastructure/Scene.hpp>

namespace snake {
	enum SnakeGroup : std::size_t {
		GApple,
		GSnakeHead,
		GSnakeBody,
		GSnake
	};
	class GameScene : public inf::Scene {
	public:
		GameScene(SnakeConfigurationManager& _configuration);
		~GameScene(void) override;
		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		void initialize(void);

	private:
		void initializeBoardGraphic(unsigned int _width, unsigned int _height);

		void createRandomApple(void);
		void growSnake(int _count);

		ecs::Entity& createAppleEntity(const sf::Vector2u& _tilePosition, int _points, int _growth, float _speedup);
		ecs::Entity& createSnakeHeadEntity(const sf::Vector2u& _tilePosition, inf::Orientation _orientation);
		ecs::Entity& createSnakeBodyEntity(const sf::Vector2u& _tilePosition, inf::Orientation _orientation, ecs::Entity *_parent);

	private:
		SnakeConfigurationManager &m_Configuration;
		ecs::EntityManager m_EntityManager;

		sf::VertexArray m_BoardVertexArray;
		unsigned int m_BoardWidth;
		unsigned int m_BoardHeight;
	};
}

#endif // INCLUDED_SNAKE_SCENES_GAME_SCENE_HPP_