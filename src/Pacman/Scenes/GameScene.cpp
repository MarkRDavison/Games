#include <Pacman/Scenes/GameScene.hpp>

#include <Pacman/Components/PositionComponent.hpp>
#include <Pacman/Components/SpriteComponent.hpp>
#include <Pacman/Components/PacmanAnimationComponent.hpp>
#include <Pacman/Components/PacmanPlayerControlComponent.hpp>
#include <Pacman/Components/GhostAnimationComponent.hpp>

#include <iostream>
#include <Pacman/Components/GhostControlComponent.hpp>

namespace pacman {

	GameScene::GameScene(inf::TextureManager& _textureManager, Board *_board) :
		inf::Scene("pacman::GameScene"),
		m_TextureManager(_textureManager),
		m_Board(_board) {

	}

	GameScene::~GameScene(void) {

	}


	void GameScene::update(float _delta) {
		m_Board->update(_delta);
		m_EntityManager.update(_delta);
		m_EntityManager.refresh();
	}

	bool GameScene::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::F6) {
				initialize();
				return true;
			}
		}
		return false;
	}

	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		sf::RenderStates boardStates(_states);
		boardStates.transform.translate(-0.5f, -0.5f);
		//boardStates.texture = &m_TextureManager.getTexture("spritemap");
		_target.draw(*m_Board, boardStates);
		m_EntityManager.draw(_target, _states);
	}

	void GameScene::initialize(void) {
		std::cout << "Initializing Pacman" << std::endl;
		m_EntityManager.applyActionToAllEntities([](ecs::Entity& _e) { _e.destroy(); });
		m_EntityManager.refresh();

		m_Board->initialize();

		createPacman({ 13.5f, 26.0f });
		createGhost({ 13.5f, 14.0f }, GhostType::Red);
		createGhost({ 12.5f, 17.0 }, GhostType::Blue);
		createGhost({ 13.5f, 17.0f }, GhostType::Pink);
		createGhost({ 14.5f, 17.0 }, GhostType::Yellow);
	}

	void GameScene::createPacman(const sf::Vector2f& _position) {
		ecs::Entity& e = m_EntityManager.addEntity();
		e.addComponent<PositionComponent>(_position);
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("spritemap"));
		e.addComponent<PacmanAnimationComponent>();
		auto& pc = e.addComponent<PacmanControlComponent>(m_Board);
		pc.cellEntered = [](const sf::Vector2i& _cell) {
			std::cout << "Pacman entered " << _cell.x << ", " << _cell.y << std::endl;
		};
	}

	void GameScene::createGhost(const sf::Vector2f& _position, GhostType _type) {
		ecs::Entity& e = m_EntityManager.addEntity();
		e.addComponent<PositionComponent>(_position);
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("spritemap"));
		e.addComponent<GhostAnimationComponent>(_type);
		e.addComponent<GhostControlComponent>();
	}
}
