#include <Castle/Infrastructure/EntityPrototypeFactory.hpp>
#include <Castle/Infrastructure/EntityGroups.hpp>
#include <Castle/Components/PositionComponent.hpp>
#include <Castle/Components/SpriteComponent.hpp>
#include <Castle/Components/PlayerComponent.hpp>
#include <Castle/Components/RectangleComponent.hpp>
#include <Castle/Components/HealthComponent.hpp>
#include <Castle/Components/TimerComponent.hpp>
#include <Castle/Components/WaypointComponent.hpp>
#include <Utility/Colour.hpp>
#include <iostream>

namespace castle {

	EntityPrototypeFactory::EntityPrototypeFactory(inf::TextureManager& _textureManager) :
		m_TextureManager(_textureManager) {
		
	}
	EntityPrototypeFactory::~EntityPrototypeFactory(void) {
		
	}


	void EntityPrototypeFactory::createEntityFromPrototype(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) {
		if (_parsedEntity.prototype == "coin") {
			createCoinEntity(_entityManager, _parsedEntity);
		}
		else if (_parsedEntity.prototype == "ladder") {
			createLadderEntity(_entityManager, _parsedEntity);
		}
		else if (_parsedEntity.prototype == "flame") {
			createFlameEntity(_entityManager, _parsedEntity);
		}
		else if (_parsedEntity.prototype == "moving_platform") {
			createMovingPlatformEntity(_entityManager, _parsedEntity);
		}
		else if (_parsedEntity.prototype == "player") {
			createMovingPlayerEntity(_entityManager, _parsedEntity);
		}
		else if (_parsedEntity.prototype == "level_transition") {
			createLevelTransitionEntity(_entityManager, _parsedEntity);
		}
	}

	void EntityPrototypeFactory::createCoinEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const {
		ecs::Entity& e = _entityManager.addEntity(_parsedEntity.name);
		e.addGroup(EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(_parsedEntity.coordinates) + sf::Vector2f(0.5f, 1.0f));
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("coin"), sf::IntRect(0, 0, 16, 16));
		e.addComponent<CollisionComponent>(sf::Vector2f(0.5f, 0.5f)).callback = [](CollisionComponent& _coinCollisionComponent, CollisionComponent& _otherCollisionComponent) {
			if (_otherCollisionComponent.entity->hasComponent<PlayerComponent>()) {
				_coinCollisionComponent.entity->destroy();
			}
		};
	}
	void EntityPrototypeFactory::createLadderEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const {
		auto& e = _entityManager.addEntity(_parsedEntity.name);
		e.addGroup(EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(_parsedEntity.coordinates) + sf::Vector2f(0.5f, 1.0f));
		e.addComponent<RectangleComponent>(sf::Vector2f(_parsedEntity.size), inf::Colour::HotPink);
		e.addComponent<CollisionComponent>(sf::Vector2f(_parsedEntity.size));
		e.getComponent<CollisionComponent>().impactsMovement = true;
		e.getComponent<CollisionComponent>().effectedByGravity = false;
		e.getComponent<CollisionComponent>().canBeMovedByOthers = false;
		e.getComponent<CollisionComponent>().canMoveOthers = true;
		e.getComponent<CollisionComponent>().isClimeable = true;
		e.getComponent<CollisionComponent>().isOneWay = true;
	}
	void EntityPrototypeFactory::createFlameEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const {
		auto& e = _entityManager.addEntity(_parsedEntity.name);
		e.addGroup(EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(_parsedEntity.coordinates) + sf::Vector2f(0.5f, 1.0f));
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("flame"), sf::IntRect(0, 0, 32, 32));
		e.getComponent<SpriteComponent>().flipHorizontal = _parsedEntity.entityTable["flip"]["x"];
		e.getComponent<SpriteComponent>().flipVertical = _parsedEntity.entityTable["flip"]["y"];
		e.addComponent<CollisionComponent>(_parsedEntity.size).callback = [](CollisionComponent& _flameCollisionComponent, CollisionComponent& _otherCollisionComponent) {
			if (_otherCollisionComponent.entity->hasComponent<HealthComponent>()) {
				HealthComponent& health = _otherCollisionComponent.entity->getComponent<HealthComponent>();
				if (health.currentDamageCooldown <= 0.0f) {
					health.health -= 3;
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
	void EntityPrototypeFactory::createMovingPlatformEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const {
		auto& e = _entityManager.addEntity(_parsedEntity.name);
		e.addGroup(EntityGroup::GCollideable);
		e.addGroup(EntityGroup::GKinematic);
		e.addGroup(EntityGroup::GWaypoint);
		e.addComponent<PositionComponent>(sf::Vector2f(_parsedEntity.coordinates) + sf::Vector2f(0.5f, 1.0f));
		e.addComponent<RectangleComponent>(_parsedEntity.size, sf::Color(
			_parsedEntity.entityTable["color"]["r"],
			_parsedEntity.entityTable["color"]["g"], 
			_parsedEntity.entityTable["color"]["b"]
		));
		e.addComponent<CollisionComponent>(_parsedEntity.size);
		e.getComponent<CollisionComponent>().impactsMovement = _parsedEntity.entityTable["impacts_movement"];
		e.getComponent<CollisionComponent>().effectedByGravity = _parsedEntity.entityTable["effected_by_gravity"];
		e.getComponent<CollisionComponent>().canBeMovedByOthers = _parsedEntity.entityTable["can_be_moved_by_others"];
		e.getComponent<CollisionComponent>().canMoveOthers = _parsedEntity.entityTable["can_move_others"];
		e.getComponent<CollisionComponent>().isOneWay = _parsedEntity.entityTable["is_one_way"];
		e.addComponent<WaypointComponent>();
		sol::table waypointTable = _parsedEntity.entityTable["waypoints"];
		for (unsigned int i = 1; i <= waypointTable.size(); ++i) {
			sol::table waypoint = waypointTable[i];
			e.getComponent<WaypointComponent>().waypoints.push_back(std::make_pair(sf::Vector2f(waypoint["x"], waypoint["y"]) + sf::Vector2f(0.5f, 1.0f), waypoint["speed"]));
		}
	}
	void EntityPrototypeFactory::createMovingPlayerEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const {
		auto& e = _entityManager.addEntity(_parsedEntity.name);
		e.addGroup(EntityGroup::GPlayer);
		e.addGroup(EntityGroup::GKinematic);
		e.addGroup(EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(_parsedEntity.coordinates) + sf::Vector2f(0.5f, 1.0f));
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("player"), sf::IntRect(0, 0, 32, 48));
		e.addComponent<HealthComponent>(_parsedEntity.entityTable["max_health"], _parsedEntity.entityTable["starting_health"]);
		e.addComponent<PlayerComponent>();
		e.addComponent<CollisionComponent>(_parsedEntity.size);
		e.getComponent<CollisionComponent>().canBeMovedByOthers = true;
		e.getComponent<CollisionComponent>().canMoveOthers = true;
	}
	void EntityPrototypeFactory::createLevelTransitionEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const {
		ecs::Entity& e = _entityManager.addEntity(_parsedEntity.name);
		e.addGroup(EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(_parsedEntity.coordinates) + sf::Vector2f(0.5f, 1.0f));
		e.addComponent<RectangleComponent>(_parsedEntity.size, sf::Color(
			_parsedEntity.entityTable["color"]["r"],
			_parsedEntity.entityTable["color"]["g"],
			_parsedEntity.entityTable["color"]["b"]
		));
		e.addComponent<CollisionComponent>(_parsedEntity.size).callback = [](CollisionComponent& _coinCollisionComponent, CollisionComponent& _otherCollisionComponent) {
			if (_otherCollisionComponent.entity->hasComponent<PlayerComponent>()) {
				std::cout << "Move to another level" << std::endl; // TODO: How do we acces the game scene from this point? Message system?
			}
		};
	}
}
