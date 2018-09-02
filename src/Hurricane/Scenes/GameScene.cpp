#include <Hurricane/Scenes/GameScene.hpp>
#include <EntityComponentSystem/EntityManager.hpp>
#include <EntityComponentSystem/Entity.hpp>
#include <iostream>

namespace hur {

	GameScene::GameScene(
		inf::TextureManager& _textureManager, CollisionSystem& _collisionSystem, KinematicSystem& _kinematicSystem, 
		PlayerControlSystem& _playerControlSystem, ProjectileControlSystem& _projectileControlSystem, PickupControlSystem& _pickupControlSystem, EntityFactory& _entityFactory)
	:
		inf::Scene("hur::GameScene"),
		m_Level(nullptr),
		m_TextureManager(_textureManager),
		m_CollisionSystem(_collisionSystem),
		m_KinematicSystem(_kinematicSystem),
		m_PlayerControlSystem(_playerControlSystem),
		m_ProjectileControlSystem(_projectileControlSystem),
		m_PickupControlSystem(_pickupControlSystem),
		m_EntityFactory(_entityFactory) {
		
	}
	GameScene::~GameScene(void) {
		
	}

	void GameScene::update(float _delta) {
		if (m_Level != nullptr) {
			ecs::EntityManager& em = m_Level->getEntityManager();
			em.update(_delta);

			m_PlayerControlSystem.update(_delta, em);

			m_ProjectileControlSystem.update(_delta, em);

			m_PickupControlSystem.update(_delta, em);

			m_CollisionSystem.update(_delta, em);

			m_KinematicSystem.update(_delta, em);

			em.refresh();
		}
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		if (m_Level != nullptr) {
			ecs::EntityManager& em = m_Level->getEntityManager();

			if (m_PlayerControlSystem.handleEvent(_event, em)) {
				return true;
			}
			if (m_ProjectileControlSystem.handleEvent(_event, em)) {
				return true;
			}
			if (m_PickupControlSystem.handleEvent(_event, em)) {
				return true;
			}
			if (m_CollisionSystem.handleEvent(_event, em)) {
				return true;
			}
			if (m_KinematicSystem.handleEvent(_event, em)) {
				return true;
			}
		}
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		if (m_Level != nullptr) {
			ecs::EntityManager& em = m_Level->getEntityManager();
			em.draw(_target, _states);
		}
	}

	void GameScene::addPlayer(void) {
		if (m_Level == nullptr) {
			std::cout << "Cannot add player when level does not exist." << std::endl;
			return;
		}

		m_EntityFactory.createPlayer(m_Level->getEntityManager());

	}
	void GameScene::addEnemy(int _index, const sf::Vector2f& _position) {
		if (m_Level == nullptr) {
			std::cout << "Cannot add enemy when level does not exist." << std::endl;
			return;
		}
		
		m_EntityFactory.createBlackEnemy(m_Level->getEntityManager(), _index, _position);
	}
}
