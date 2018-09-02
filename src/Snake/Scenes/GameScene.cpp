#include <Snake/Scenes/GameScene.hpp>

#include <Snake/Components/AppleComponent.hpp>
#include <Snake/Components/CircleComponent.hpp>
#include <Snake/Components/PositionComponent.hpp>
#include <Snake/Components/SnakeComponent.hpp>

#include <Utility/Colour.hpp>

#include <iostream>
#include <Snake/Infrastructure/SnakeConfigurationManager.hpp>

namespace snake {

	GameScene::GameScene(SnakeConfigurationManager& _configuration) :
		inf::Scene("snake::GameScene"),
		m_Configuration(_configuration),
		m_BoardWidth(0),
		m_BoardHeight(0) {
		
	}
	GameScene::~GameScene(void) {
		
	}
	void GameScene::update(float _delta) {
		m_EntityManager.update(_delta);
		m_EntityManager.refresh();

	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::F6) {
				m_Configuration.reloadConfiguration();
				initialize();
				return true;
			}
		}
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		_target.draw(m_BoardVertexArray, _states);
		m_EntityManager.draw(_target, _states);
	}

	void GameScene::initialize(void) {
		std::cout << "Initlializing snake" << std::endl;
		m_EntityManager.applyActionToAllEntities([](ecs::Entity& _e) { _e.destroy(); });
		m_EntityManager.refresh();

		initializeBoardGraphic(m_Configuration.GetGameWidth(), m_Configuration.GetGameHeight());
	}

	void GameScene::initializeBoardGraphic(unsigned int _width, unsigned int _height) {
		m_BoardVertexArray.clear();
		m_BoardWidth = _width;
		m_BoardHeight = _height;

		m_BoardVertexArray = sf::VertexArray(sf::Triangles, 3 * 2 * m_BoardWidth * m_BoardHeight);

		const float spacing = 0.05f;

		for (unsigned int y = 0; y < m_BoardHeight; ++y) {
			for (unsigned int x = 0; x < m_BoardWidth; ++x) {
				m_BoardVertexArray[(y * m_BoardWidth + x) * 6 + 0] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 0) + spacing, static_cast<float>(y + 0) + spacing), sf::Color::Green);
				m_BoardVertexArray[(y * m_BoardWidth + x) * 6 + 1] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 1) - spacing, static_cast<float>(y + 0) + spacing), sf::Color::Green);
				m_BoardVertexArray[(y * m_BoardWidth + x) * 6 + 2] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 1) - spacing, static_cast<float>(y + 1) - spacing), sf::Color::Green);

				m_BoardVertexArray[(y * m_BoardWidth + x) * 6 + 3] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 0) + spacing, static_cast<float>(y + 0) + spacing), sf::Color::Green);
				m_BoardVertexArray[(y * m_BoardWidth + x) * 6 + 4] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 1) - spacing, static_cast<float>(y + 1) - spacing), sf::Color::Green);
				m_BoardVertexArray[(y * m_BoardWidth + x) * 6 + 5] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 0) + spacing, static_cast<float>(y + 1) - spacing), sf::Color::Green);
			}
		}

		auto& head = createSnakeHeadEntity({ 6, 6 }, inf::Orientation::Up);
		auto& body = createSnakeBodyEntity({ 6, 7 }, inf::Orientation::Up, &head);
		createSnakeBodyEntity({ 6, 8 }, inf::Orientation::Up, &body);
		createRandomApple();
	}

	void GameScene::createRandomApple(void) {
		createAppleEntity(
			{ rand() % m_BoardWidth, rand() % m_BoardHeight },
			1,1,0.95f
		);
		
	}
	void GameScene::growSnake(int _count) {
		
		ecs::Entity *tail{ m_EntityManager.getEntitiesByGroup(SnakeGroup::GSnakeHead).front() };
		for (auto& snake : m_EntityManager.getEntitiesByGroup(SnakeGroup::GSnake)) {
			if (tail->getComponent<SnakeComponent>().index < snake->getComponent<SnakeComponent>().index) {
				tail = snake;
			}
		}

		createSnakeBodyEntity(sf::Vector2u(tail->getComponent<PositionComponent>().position), tail->getComponent<SnakeComponent>().orientation, tail);
	}

	ecs::Entity& GameScene::createAppleEntity(const sf::Vector2u& _tilePosition, int _points, int _growth, float _speedup) {
		ecs::Entity& apple = m_EntityManager.addEntity();

		apple.addComponent<PositionComponent>(sf::Vector2f{ static_cast<float>(_tilePosition.x) + 0.5f, static_cast<float>(_tilePosition.y) + 0.5f });
		auto& cApple = apple.addComponent<AppleComponent>();
		cApple.points = _points;
		cApple.growth = _growth;
		cApple.speedup = _speedup;
		apple.addComponent<CircleComponent>(0.2f);
		apple.getComponent<CircleComponent>().shape.setFillColor(inf::Colour::BrickRed);

		apple.addGroup(SnakeGroup::GApple);

		return apple;
	}

	ecs::Entity& GameScene::createSnakeHeadEntity(const sf::Vector2u& _tilePosition, inf::Orientation _orientation) {
		ecs::Entity& snake = m_EntityManager.addEntity();

		snake.addComponent<PositionComponent>(sf::Vector2f{ static_cast<float>(_tilePosition.x) + 0.5f, static_cast<float>(_tilePosition.y) + 0.5f });
		auto& sc = snake.addComponent<SnakeComponent>(nullptr, m_Configuration.getInitialTickSpeed(), _orientation);
		sc.onParentEnteringCell = [&](SnakeComponent *_head, const sf::Vector2f& _position) {

			if (_position.x < 0.0f || _position.y < 0.0f || _position.x > static_cast<float>(m_BoardWidth) || _position.y > static_cast<float>(m_BoardHeight)) {
				std::cout << "Snake hit the wall!" << std::endl;
				return false;
			}

			auto& snakeBodies = m_EntityManager.getEntitiesByGroup(SnakeGroup::GSnakeBody);
			for (auto& body : snakeBodies) {
				if (_position == body->getComponent<PositionComponent>().position) {
					std::cout << "Collided with body" << std::endl;
					_head->dead = true;
					return false;
				}
			}

			auto& apples = m_EntityManager.getEntitiesByGroup(SnakeGroup::GApple);
			for (auto& apple : apples) {
				if (_position == apple->getComponent<PositionComponent>().position) {
					apple->destroy();
					AppleComponent& ac = apple->getComponent<AppleComponent>();

					createRandomApple();
					growSnake(ac.growth);
					_head->timeToMoveCap *= ac.speedup;
					std::cout << "PICK UP APPLE, points: " << ac.points << ", growth: " << ac.growth << ", speedup: " << ac.speedup << std::endl;
				}
			}

			return true;
		};

		snake.addComponent<CircleComponent>(0.4f);
		snake.getComponent<CircleComponent>().shape.setFillColor(inf::Colour::Purple);

		snake.addGroup(SnakeGroup::GSnakeHead);
		snake.addGroup(SnakeGroup::GSnake);

		return snake;
	}

	ecs::Entity& GameScene::createSnakeBodyEntity(const sf::Vector2u& _tilePosition, inf::Orientation _orientation, ecs::Entity* _parent) {
		ecs::Entity& snake = m_EntityManager.addEntity();

		snake.addComponent<PositionComponent>(sf::Vector2f{ static_cast<float>(_tilePosition.x) + 0.5f, static_cast<float>(_tilePosition.y) + 0.5f });		
		snake.addComponent<SnakeComponent>(&_parent->getComponent<SnakeComponent>(), 0.0f, _orientation);
		snake.addComponent<CircleComponent>(0.35f);
		snake.getComponent<CircleComponent>().shape.setFillColor(inf::Colour::DarkGrey);

		snake.addGroup(SnakeGroup::GSnakeBody);
		snake.addGroup(SnakeGroup::GSnake);

		return snake;
		
	}
}
