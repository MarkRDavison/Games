#include <Intrusion/Scenes/GameScene.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {

	GameScene::GameScene(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager) :
		inf::Scene("itr::GameScene"),
		m_TextureManager(_textureManager),
		m_EntityManager(_entityManager) {
		
	}
	GameScene::~GameScene(void) {
		
	}

	void GameScene::update(float _delta) {
		if (m_Level != nullptr) {
			m_Level->update(_delta);
		}
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		if (m_Level != nullptr) {
			if (m_Level->handleEvent(_event)) {
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
	}

}
