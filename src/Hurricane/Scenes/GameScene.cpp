#include <Hurricane/Scenes/GameScene.hpp>
#include <Hurricane/Components/CollisionComponent.hpp>
#include <Hurricane/Components/PlayerComponent.hpp>
#include <Hurricane/Components/PositionComponent.hpp>
#include <Hurricane/Components/SpriteComponent.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>
#include <EntityComponentSystem/Entity.hpp>
#include <iostream>
#include <Hurricane/Components/MovementComponent.hpp>

namespace hur {

	GameScene::GameScene(inf::TextureManager& _textureManager, CollisionSystem& _collisionSystem, KinematicSystem& _kinematicSystem, PlayerControlSystem& _playerControlSystem, ProjectileControlSystem& _projectileControlSystem) :
		inf::Scene("hur::GameScene"),
		m_Level(nullptr),
		m_TextureManager(_textureManager),
		m_CollisionSystem(_collisionSystem),
		m_KinematicSystem(_kinematicSystem),
		m_PlayerControlSystem(_playerControlSystem),
		m_ProjectileControlSystem(_projectileControlSystem) {
		
	}
	GameScene::~GameScene(void) {
		
	}

	void GameScene::update(float _delta) {
		if (m_Level != nullptr) {
			ecs::EntityManager& em = m_Level->getEntityManager();
			em.update(_delta);

			m_PlayerControlSystem.update(_delta, em);

			m_ProjectileControlSystem.update(_delta, em);

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
			if (m_CollisionSystem.handleEvent(_event, em)) {
				return true;
			}
			if (m_KinematicSystem.handleEvent(_event, em)) {
				return true;
			}
		}
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
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

		ecs::Entity& e = m_Level->getEntityManager().addEntity("Player");
		e.addGroup(hurr::EntityGroup::GPlayer);
		e.addGroup(hurr::EntityGroup::GKinematic);
		e.addGroup(hurr::EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(10.0f, 15.0f));
		e.addComponent<MovementComponent>();
		e.addComponent<PlayerComponent>();
		sf::Vector2f size{99.0f, 75.0f};
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("player_ship"), sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		e.addComponent<CollisionComponent>(sf::Vector2f(size.x / 64.0f, size.y / 64.0f));
	}
	void GameScene::addEnemy(int _index, const sf::Vector2f& _position) {
		ecs::Entity& e = m_Level->getEntityManager().addEntity();
		e.addGroup(hurr::EntityGroup::GEnemy);
		e.addGroup(hurr::EntityGroup::GKinematic);
		e.addGroup(hurr::EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(_position);
		e.addComponent<MovementComponent>();

		std::string textureName;
		sf::Vector2f size{};
		switch (_index) {
		case 1:
			textureName = "enemy_ship_black_1";
			size = { 93.0f, 84.0f };
			break;
		case 2:
			textureName = "enemy_ship_black_2";
			size = { 104.0f, 84.0f };
			break;
		case 3:
			textureName = "enemy_ship_black_3";
			size = { 103.0f, 84.0f };
			break;
		case 4:
			textureName = "enemy_ship_black_4";
			size = { 82.0f, 84.0f };
			break;
		default:
			textureName = "enemy_ship_black_5";
			size = { 97.0f, 84.0f };
			break;
		}

		e.addComponent<SpriteComponent>(m_TextureManager.getTexture(textureName), sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		e.addComponent<CollisionComponent>(sf::Vector2f(size.x / 64.0f, size.y / 64.0f));
	}
}
