#include <Intrusion/Scenes/GameScene.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {

	GameScene::GameScene(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager, EntityFactory& _entityFactory, RenderSystem& _renderSystem, PathFollowingSystem& _pathFollowingSystem, ProjectileControlSystem& _projectileControlSystem, TowerFiringSystem& _towerFiringSystem, TowerTargetingSystem& _towerTargetingSystem, LifeSystem& _lifeSystem) :
		inf::Scene("itr::GameScene"),
		m_TextureManager(_textureManager),
		m_EntityManager(_entityManager),
		m_EntityFactory(_entityFactory),
		m_RenderSystem(_renderSystem),
		m_PathFollowingSystem(_pathFollowingSystem),
		m_ProjectileControlSystem(_projectileControlSystem),
		m_TowerFiringSystem(_towerFiringSystem),
		m_TowerTargetingSystem(_towerTargetingSystem),
		m_LifeSystem(_lifeSystem) {
		
		m_TowerFiringSystem.projectileSpawned = [&](const ParsedProjectile& _prototype, ecs::Entity *_source, ecs::Entity *_target) {
			m_EntityFactory.spawnProjectileFromPrototype(_prototype, _source, _target);
		};
	}
	GameScene::~GameScene(void) {
		
	}

	void GameScene::update(float _delta) {
		m_EntityManager.update(_delta);

		if (m_Level != nullptr) {
			m_Level->update(_delta);
		}

		m_RenderSystem.update(_delta, m_EntityManager);

		m_PathFollowingSystem.update(_delta, m_EntityManager);

		m_TowerTargetingSystem.update(_delta, m_EntityManager);

		m_TowerFiringSystem.update(_delta, m_EntityManager);

		m_ProjectileControlSystem.update(_delta, m_EntityManager);

		m_LifeSystem.update(_delta, m_EntityManager);

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
