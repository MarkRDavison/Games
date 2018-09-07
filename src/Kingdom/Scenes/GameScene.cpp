#include <Kingdom/Scenes/GameScene.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>
#include <Infrastructure/Application.hpp>
#include <Kingdom/Components/PathfindingComponent.hpp>

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

}
