#include <Kingdom/Scenes/GameScene.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>
#include <Infrastructure/Application.hpp>
#include <Kingdom/Components/PathfindingComponent.hpp>
#include <Kingdom/Components/PositionComponent.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>

namespace kdm {

	GameScene::GameScene(std::function<sf::Vector2f(const sf::Vector2i&)>& _convertToGameCoords, ecs::EntityManager& _entityManager, inf::TextureManager& _textureManager, EntityFactory& _entityFactory,
		RenderSystem& _renderSystem, MovementSystem& _movementSystem, WaypointSytem& _waypointSytem, PathfindingSystem& _pathfindingSystem) :
		inf::Scene("kdm::GameScene"),
		m_ScreenToGameCoords(_convertToGameCoords),
		m_EntityFactory(_entityFactory),
		m_EntityManager(_entityManager),
		m_TextureManager(_textureManager),
		m_RenderSystem(_renderSystem),
		m_MovementSystem(_movementSystem),
		m_WaypointSystem(_waypointSytem),
		m_PathfindingSystem(_pathfindingSystem) {
		
	}
	GameScene::~GameScene(void) {
		
	}

	void GameScene::update(float _delta) {
		m_EntityManager.update(_delta);

		if (m_Level != nullptr) {
			m_Level->update(_delta);
		}

		m_PathfindingSystem.update(_delta, m_EntityManager);

		m_WaypointSystem.update(_delta, m_EntityManager);

		m_MovementSystem.update(_delta, m_EntityManager);

		m_EntityManager.refresh();
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		if (m_Level != nullptr) {
			if (m_Level->handleEvent(_event)) {
				return true;
			}
		}

		if (m_PathfindingSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}

		if (m_WaypointSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}

		if (m_MovementSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}

		if (_event.type == sf::Event::MouseButtonPressed) {
			if (handleMouseClicked(_event)) {
				return true;
			}
		}

		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		if (m_Level != nullptr) {
			_states.texture = &m_TextureManager.getTexture(Definitions::TerrainTextureName);
			_target.draw(*m_Level, _states);
			_states.texture = nullptr;
		}

		m_RenderSystem.draw(m_EntityManager, _target, _states, _alpha);
	}

	bool GameScene::handleMouseClicked(const sf::Event& _event) const {
		if (_event.mouseButton.button == sf::Mouse::Left) {
			const sf::Vector2i screenCoords(_event.mouseButton.x, _event.mouseButton.y);
			const sf::Vector2f worldCoords = m_ScreenToGameCoords(screenCoords);
			const sf::Vector2i tileCoords(worldCoords);

			ecs::Entity& e = m_EntityManager.getEntity("Gear");
			PathfindingComponent& pc = e.getComponent<PathfindingComponent>();
			WaypointComponent& wc = e.getComponent<WaypointComponent>();
			if (!pc.pathRequested && wc.waypoints.empty()) {
				pc.pathRequested = true;
				pc.start = sf::Vector2u(e.getComponent<PositionComponent>().position);
				pc.end = sf::Vector2u(tileCoords);
			}
		}
		return false;
	}

}
