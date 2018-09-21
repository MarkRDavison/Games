#include <Intrusion/Infrastructure/EntityFactory.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/SpriteComponent.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>
#include <Intrusion/Components/CircleComponent.hpp>
#include <Intrusion/Components/TowerTargetComponent.hpp>
#include <Intrusion/Components/TowerTargetingComponent.hpp>
#include <Intrusion/Components/ProjectileComponent.hpp>
#include <Intrusion/Components/TowerFiringComponent.hpp>
#include <Intrusion/Components/LifeComponent.hpp>

namespace itr {

	EntityFactory::EntityFactory(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager, IntrusionConfigurationManager& _configurationManager, LuaEntityParser& _luaEntityParser, LuaTowerParser& _luaTowerParser) :
		m_TextureManager(_textureManager),
		m_EntityManager(_entityManager),
		m_ConfigurationManager(_configurationManager),
		m_LuaEntityParser(_luaEntityParser),
		m_LuaTowerParser(_luaTowerParser) {
		
	}
	EntityFactory::~EntityFactory(void) {
		
	}

	// TODO: Should only was the prototype name to this and return the entity reference to set the position and the path points
	ecs::Entity& EntityFactory::spawnWaveEntityFromPrototype(const sf::Vector2u& _tilePosition, const std::string& _prototype, inf::Path& _path) {
		if (!m_LuaEntityParser.entityHasBeenParsed(_prototype)) {
			std::cout << "Cannot create entity '" << _prototype << "', it hasn't been parsed." << std::endl;
			throw std::runtime_error("Cannot create unparsed entity");
		}

		const ParsedEntity& parsedEntity = m_LuaEntityParser.getEntity(_prototype);
		const float scale = m_ConfigurationManager.getGameViewScale();
		sf::Texture& texture = m_TextureManager.getTexture(parsedEntity.animationName);
		const float offset = texture.getSize().y / 2.0f;
		ecs::Entity& e = m_EntityManager.addEntity();
		e.addGroup(EntityGroup::GRenderable);
		e.addGroup(EntityGroup::GPathFollower);
		e.addGroup(EntityGroup::GTowerTarget);
		e.addGroup(EntityGroup::GLife);
		e.addComponent<PositionComponent>(sf::Vector2f(static_cast<float>(_tilePosition.x) + 0.5f, static_cast<float>(_tilePosition.y) + 0.5f) * Definitions::TileSize);
		e.addComponent<TowerTargetComponent>();
		SpriteComponent& sc = e.addComponent<SpriteComponent>(texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y), scale);
		sc.flipHorizontal = false;
		sc.flipVertical = false;
		sc.visualOffset.y = offset;
		PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
		pfc.speed = parsedEntity.speed;
		LifeComponent& lc = e.addComponent<LifeComponent>();
		lc.health = parsedEntity.health;
		lc.onDeathResources = parsedEntity.drops;

		for (const inf::PathNode& node : _path.nodes) {
			pfc.pathPoints.push(sf::Vector2f(static_cast<float>(node.x) + 0.5f, static_cast<float>(node.y) + 0.5f) * Definitions::TileSize);
		}

		return e;
	}

	ecs::Entity& EntityFactory::spawnProjectileFromPrototype(const ParsedProjectile& _prototype, ecs::Entity* _source, ecs::Entity* _target) {
		const float scale = m_ConfigurationManager.getGameViewScale();

		ecs::Entity& e = m_EntityManager.addEntity();
		e.addGroup(EntityGroup::GRenderable);
		e.addGroup(EntityGroup::GPathFollower);
		e.addGroup(EntityGroup::GProjectile);

		e.addComponent<PositionComponent>(_source->getComponent<PositionComponent>().position);
		ProjectileComponent& pc = e.addComponent<ProjectileComponent>();
		pc.source = m_EntityManager.getWeakEntityRef(_source);
		pc.target = m_EntityManager.getWeakEntityRef(_target);
		pc.damage.health = -_prototype.baseDamage;
		CircleComponent& cc = e.addComponent<CircleComponent>(0.05f, scale);
		PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
		pfc.speed = _prototype.speed;
		pfc.pathPoints.push(_target->getComponent<PositionComponent>().position);
		pfc.pathCompleted = [](ecs::Entity *_entity) {
			std::cout << "Projectile has reached " << _entity->name << std::endl;
			ProjectileComponent& projC = _entity->getComponent<ProjectileComponent>();
			if (std::shared_ptr<ecs::Entity> t = projC.target.lock()) {
				LifeComponent& lc = t->getComponent<LifeComponent>();
				lc.lifeAdjustments.push(projC.damage);
			}
		};

		std::cout << "Spawning projectile" << std::endl;

		return e;
	}

	// TODO: ParsedTower or just the prototype name. . . . . 
	void EntityFactory::spawnTowerEntityFromPrototype(const sf::Vector2u& _tilePosition, const ParsedTower& _prototype) {
		const float scale = m_ConfigurationManager.getGameViewScale();
		sf::Texture& texture = m_TextureManager.getTexture(_prototype.animationName);
		const float offset = texture.getSize().y / 2.0f;

		ecs::Entity& e = m_EntityManager.addEntity(_prototype.prototypeName);
		e.addGroup(EntityGroup::GRenderable);
		e.addGroup(EntityGroup::GTower);
		e.addComponent<PositionComponent>(sf::Vector2f(static_cast<float>(_tilePosition.x) + 0.5f, static_cast<float>(_tilePosition.y) + 0.5f) * Definitions::TileSize);
		TowerTargetingComponent& ttc = e.addComponent<TowerTargetingComponent>();
		ttc.range = _prototype.range;
		TowerFiringComponent& tfc = e.addComponent<TowerFiringComponent>();
		tfc.firingCooldown = 1.0f;
		tfc.projectilePrototype.speed = 15.0f;
		SpriteComponent& sc = e.addComponent<SpriteComponent>(texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y), scale);
		sc.flipHorizontal = false;
		sc.flipVertical = false;
		sc.visualOffset.y = offset;
		sc.sprite.setColor(_prototype.color);
	}
}
