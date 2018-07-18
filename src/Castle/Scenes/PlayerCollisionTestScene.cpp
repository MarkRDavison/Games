#include <Castle/Scenes/PlayerCollisionTestScene.hpp>
#include <Castle/DataStructures/ParsedLevel.hpp>

#include <Castle/Infrastructure/EntityGroups.hpp>

#include <Castle/Components/PositionComponent.hpp>
#include <Castle/Components/SpriteComponent.hpp>
#include <Castle/Components/PlayerComponent.hpp>
#include <Castle/Components/RectangleComponent.hpp>
#include <Castle/Components/InteractableComponent.hpp>
#include <Castle/Components/HealthComponent.hpp>
#include <Castle/Components/CollisionComponent.hpp>
#include <Castle/Components/TimerComponent.hpp>
#include <Castle/Components/WaypointComponent.hpp>

#include <Utility/Colour.hpp>
#include <iostream>

namespace castle {

	PlayerCollisionTestScene::PlayerCollisionTestScene(inf::TextureManager& _textureManager, AutoPlayerInputManager& _inputManager, CastleConfigurationManager& _castleConfigurationManager, ecs::EntityManager& _entityManager, CollisionSystem& _collisionSystem, KinematicSystem& _kinematicSystem, PlayerControlSystem& _playerControlSystem, PlayerInteractionSystem& _playerInteractionSystem, WaypointSystem& _waypointSystem) :
		inf::Scene("castle::PlayerCollisionTestScene"),
		m_CastleConfigurationManager(_castleConfigurationManager),
		m_EntityManager(_entityManager),
		m_InputManager(_inputManager),
		m_TextureManager(_textureManager),
		m_Level(nullptr),
		m_CollisionSystem(_collisionSystem),
		m_KinematicSystem(_kinematicSystem),
		m_PlayerControlSystem(_playerControlSystem),
		m_PlayerInteractionSystem(_playerInteractionSystem),
		m_WaypointSystem(_waypointSystem) {

	}
	PlayerCollisionTestScene::~PlayerCollisionTestScene(void) {

	}

	void PlayerCollisionTestScene::update(float _delta) {
		m_EntityManager.update(_delta);

		m_PlayerControlSystem.update(_delta, m_EntityManager);
		m_PlayerInteractionSystem.update(_delta, m_EntityManager);
		m_WaypointSystem.update(_delta, m_EntityManager);
		m_CollisionSystem.update(_delta, m_EntityManager);
		m_KinematicSystem.update(_delta, m_EntityManager);
		m_CollisionSystem.handleMovementStuff(_delta, m_Level);
		m_InputManager.update(m_EntityManager.getEntitiesByGroup(EntityGroup::GPlayer).front());

		m_EntityManager.refresh();
	}
	bool PlayerCollisionTestScene::handleEvent(const sf::Event& _event) {
		if (m_PlayerControlSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}
		if (m_PlayerInteractionSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}
		if (m_WaypointSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}
		if (m_CollisionSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}
		if (m_KinematicSystem.handleEvent(_event, m_EntityManager)) {
			return true;
		}
		return false;
	}
	void PlayerCollisionTestScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		sf::RenderStates levelStates(_states);
		levelStates.texture = &m_TextureManager.getTexture("terrain");
		_target.draw(reinterpret_cast<const sf::Drawable&>(*m_Level), levelStates);
		m_EntityManager.draw(_target, _states);
	}

	void PlayerCollisionTestScene::initializeTestScene1(void) {
		m_EntityManager.applyActionToAllEntities([](ecs::Entity&e) {e.destroy(); });
		m_EntityManager.refresh();

		if (m_Level != nullptr) {
			delete m_Level;
		}

		m_Level = new Level();
		//m_Level->initialize(nullptr, ParsedLevel::createTestLevel());
		{
			auto& e = m_EntityManager.addEntity("Player");
			e.addGroup(EntityGroup::GPlayer);
			e.addGroup(EntityGroup::GKinematic);
			e.addGroup(EntityGroup::GCollideable);
			e.addComponent<PositionComponent>(sf::Vector2f(10.5f, 8.0f));
			e.addComponent<SpriteComponent>(m_TextureManager.getTexture("player"), sf::IntRect(0, 0, 32, 48));
			e.addComponent<HealthComponent>(10, 10);
			e.addComponent<PlayerComponent>();
			e.addComponent<CollisionComponent>(sf::Vector2f(1.0f, 1.5f));
			e.getComponent<CollisionComponent>().canBeMovedByOthers = true;
			e.getComponent<CollisionComponent>().canMoveOthers = true;
		}
		{
			m_Level->getCell(1, 3).empty = false;
			m_Level->getCell(1, 2).empty = false;
			auto& doorEntity = m_EntityManager.addEntity("Door");
			doorEntity.addGroup(EntityGroup::GInteractable);
			doorEntity.addComponent<PositionComponent>(sf::Vector2f(1.5f, 4.0f));
			doorEntity.addComponent<RectangleComponent>(sf::Vector2f(1.0f, 2.0f), sf::Color::Magenta);
			doorEntity.addComponent<InteractableComponent>(sf::Vector2f(1.0f, 2.0f), [&](ecs::Entity *_interactedEntity, ecs::Entity *_interactingEntity) {
				std::cout << "Entity " << _interactingEntity->name << " has interacted with the interactable entity " << _interactedEntity->name << std::endl;
				m_Level->getCell(1, 3).empty = true;
				m_Level->getCell(1, 2).empty = true;
				m_Level->getCell(13, 7).empty = false;
				m_Level->getCell(14, 6).empty = false;
				m_Level->initializeGraphics();
				_interactedEntity->destroy();
			});
		}
		{
			auto& e = m_EntityManager.addEntity("MovingPlatform-Vertical");
			e.addGroup(EntityGroup::GCollideable);
			e.addGroup(EntityGroup::GKinematic);
			e.addGroup(EntityGroup::GWaypoint);
			e.addComponent<PositionComponent>(sf::Vector2f(12.5f, 9.0f));
			e.addComponent<RectangleComponent>(sf::Vector2f(1.0f, 1.0f), inf::Colour::Orange);
			e.addComponent<CollisionComponent>(sf::Vector2f(1.0f, 1.0f));
			e.getComponent<CollisionComponent>().impactsMovement = true;
			e.getComponent<CollisionComponent>().effectedByGravity = false;
			e.addComponent<WaypointComponent>();
			e.getComponent<WaypointComponent>().waypoints.push_back(std::make_pair(sf::Vector2f(12.5f, 9.0f), 2.0f));
			e.getComponent<WaypointComponent>().waypoints.push_back(std::make_pair(sf::Vector2f(12.5f, 5.0f), 2.0f));
			e.getComponent<CollisionComponent>().canBeMovedByOthers = false;
			e.getComponent<CollisionComponent>().canMoveOthers = true;
		}
		{
			auto& e = m_EntityManager.addEntity("MovingPlatform-Horizontal");
			e.addGroup(EntityGroup::GCollideable);
			e.addGroup(EntityGroup::GKinematic);
			e.addGroup(EntityGroup::GWaypoint);
			e.addComponent<PositionComponent>(sf::Vector2f(14.5f, 12.0f));
			e.addComponent<RectangleComponent>(sf::Vector2f(1.0f, 1.0f), inf::Colour::NatureGreen);
			e.addComponent<CollisionComponent>(sf::Vector2f(1.0f, 1.0f));
			e.getComponent<CollisionComponent>().impactsMovement = true;
			e.getComponent<CollisionComponent>().effectedByGravity = false;
			e.addComponent<WaypointComponent>();
			e.getComponent<WaypointComponent>().waypoints.push_back(std::make_pair(sf::Vector2f(4.0f, 12.0f), 2.0f));
			e.getComponent<WaypointComponent>().waypoints.push_back(std::make_pair(sf::Vector2f(16.5f, 12.0f), 2.0f));
			e.getComponent<CollisionComponent>().canBeMovedByOthers = false;
			e.getComponent<CollisionComponent>().canMoveOthers = true;
		}
		{
			auto& e = m_EntityManager.addEntity("Spike");
			e.addGroup(EntityGroup::GCollideable);
			e.addComponent<PositionComponent>(sf::Vector2f(14.5f, 12.0f));
			e.addComponent<SpriteComponent>(m_TextureManager.getTexture("spike"), sf::IntRect(0, 0, 16, 16));
			e.addComponent<CollisionComponent>(sf::Vector2f(0.5f, 0.5f)).callback = [](CollisionComponent& _spikeCollisionComponent, CollisionComponent& _otherCollisionComponent) {
				if (_otherCollisionComponent.entity->hasComponent<HealthComponent>()) {
					HealthComponent& health = _otherCollisionComponent.entity->getComponent<HealthComponent>();
					if (health.currentDamageCooldown <= 0.0f) {
						health.health--;
						std::cout << "The spike hit something, health down to " << health.health << std::endl;
						health.currentDamageCooldown = health.damageCooldown;
						if (health.health <= 0) {
					_otherCollisionComponent.entity->destroy();
						}
					}
				}
			};
		}
		{
			std::vector<sf::Vector2i> flameTileLocations = {
				{ 21,8 },{ 3,4 },{ 7,6 }
			};
			for (const sf::Vector2i& _coord : flameTileLocations) {
				auto& e = m_EntityManager.addEntity("Flame_X_" + std::to_string(_coord.x) + "_Y_" + std::to_string(_coord.y));
				e.addGroup(EntityGroup::GCollideable);
				e.addComponent<PositionComponent>(sf::Vector2f(_coord) + sf::Vector2f(0.5f, 1.0f));
				e.addComponent<SpriteComponent>(m_TextureManager.getTexture("flame"), sf::IntRect(0, 0, 32, 32)).flipHorizontal = false;
				e.addComponent<CollisionComponent>(sf::Vector2f(1.0f, 1.0f)).callback = [](CollisionComponent& _flameCollisionComponent, CollisionComponent& _otherCollisionComponent) {
					if (_otherCollisionComponent.entity->hasComponent<HealthComponent>()) {
						HealthComponent& health = _otherCollisionComponent.entity->getComponent<HealthComponent>();
						if (health.currentDamageCooldown <= 0.0f) {
							health.health -= 3;
							std::cout << "The flame hit something, health down to " << health.health << std::endl;
							health.currentDamageCooldown = health.damageCooldown;
							if (health.health <= 0) {
								_otherCollisionComponent.entity->destroy();
							}
						}
					}
				};
				e.getComponent<CollisionComponent>().collisionThreshold = 0.1f;
				e.addComponent<TimerComponent>(1.0f, 3.0f).elapsedCallback = [](ecs::Entity *_entity) {
					TimerComponent& tc = _entity->getComponent<TimerComponent>();
					CollisionComponent& cc = _entity->getComponent<CollisionComponent>();
					SpriteComponent& sc = _entity->getComponent<SpriteComponent>();
					tc.timeRemaining += tc.time;
					if (cc.canCollide) {
						cc.canCollide = false;
						sc.render = false;
					}
					else {
						cc.canCollide = true;
						sc.render = true;
					}
				};
			}
		}
		{
			std::vector<sf::Vector2i> coinTileLocations = {
				{ 2,3 },{ 1,9 },{ 2,9 },{ 5,8 },{ 6,8 },{ 5,5 },{ 6,5 },{ 9,7 },{ 10,7 },{ 17,3 },{ 18,3 },{ 21,7 },{ 12,3 }
			};

			for (const sf::Vector2i& _coord : coinTileLocations) {
				auto& e = m_EntityManager.addEntity("Coin_X_" + std::to_string(_coord.x) + "_Y_" + std::to_string(_coord.y));
				e.addGroup(EntityGroup::GCollideable);
				e.addComponent<PositionComponent>(sf::Vector2f(_coord) + sf::Vector2f(0.5f, 1.0f));
				e.addComponent<SpriteComponent>(m_TextureManager.getTexture("coin"), sf::IntRect(0, 0, 16, 16));
				e.addComponent<CollisionComponent>(sf::Vector2f(0.5f, 0.5f)).callback = [](CollisionComponent& _coinCollisionComponent, CollisionComponent& _otherCollisionComponent) {
					if (_otherCollisionComponent.entity->hasComponent<PlayerComponent>()) {
						_coinCollisionComponent.entity->destroy();
					}
				};
			}
		}

		m_Level->initializeGraphics();
	}
}