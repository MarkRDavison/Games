#include <Intrusion/Scenes/GameScene.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {

	GameScene::GameScene(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager, RenderSystem& _renderSystem, PathFollowingSystem& _pathFollowingSystem) :
		inf::Scene("itr::GameScene"),
		m_TextureManager(_textureManager),
		m_EntityManager(_entityManager),
		m_RenderSystem(_renderSystem),
		m_PathFollowingSystem(_pathFollowingSystem) {
		
	}
	GameScene::~GameScene(void) {
		
	}

	void GameScene::update(float _delta) {
		m_EntityManager.update(_delta);

		if (m_Level != nullptr) {
			m_Level->update(_delta);
		}

		m_PathFollowingSystem.update(_delta, m_EntityManager);

		m_EntityManager.refresh();
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		if (m_Level != nullptr) {
			if (m_Level->handleEvent(_event)) {
				return true;
			}
		}
		
		if (m_PathFollowingSystem.handleEvent(_event, m_EntityManager)) {
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
