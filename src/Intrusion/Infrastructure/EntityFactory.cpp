#include <Intrusion/Infrastructure/EntityFactory.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/SpriteComponent.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>
#include <Intrusion/Components/CircleComponent.hpp>

namespace itr {

	EntityFactory::EntityFactory(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager, IntrusionConfigurationManager& _configurationManager, LuaEntityParser& _luaEntityParser) :
		m_TextureManager(_textureManager),
		m_EntityManager(_entityManager),
		m_ConfigurationManager(_configurationManager),
		m_LuaEntityParser(_luaEntityParser) {
		
	}
	EntityFactory::~EntityFactory(void) {
		
	}

	// TODO: Should only was the prototype name to this and return the entity reference to set the position and the path points
	void EntityFactory::spawnWaveEntityFromPrototype(const sf::Vector2u& _tilePosition, const std::string& _prototype, inf::Path& _path) {
		if (!m_LuaEntityParser.entityHasBeenParsed(_prototype)) {
			std::cout << "Cannot create entity '" << _prototype << "', it hasn't been parsed." << std::endl;
			return;
		}

		const ParsedEntity& parsedEntity = m_LuaEntityParser.getEntity(_prototype);
		const float scale = m_ConfigurationManager.getGameViewScale();
		sf::Texture& texture = m_TextureManager.getTexture(parsedEntity.animationName);
		const float offset = texture.getSize().y / 2.0f;

		ecs::Entity& e = m_EntityManager.addEntity(_prototype);
		e.addGroup(EntityGroup::GRenderable);
		e.addGroup(EntityGroup::GPathFollower);
		e.addComponent<PositionComponent>(sf::Vector2f(static_cast<float>(_tilePosition.x) + 0.5f, static_cast<float>(_tilePosition.y) + 0.5f) * Definitions::TileSize);
		SpriteComponent& sc = e.addComponent<SpriteComponent>(texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y), scale);
		sc.flipHorizontal = false;
		sc.flipVertical = false;
		sc.visualOffset.y = offset;
		PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
		pfc.speed = parsedEntity.speed;

		for (const inf::PathNode& node : _path.nodes) {
			pfc.pathPoints.push(sf::Vector2f(static_cast<float>(node.x) + 0.5f, static_cast<float>(node.y) + 0.5f) * Definitions::TileSize);
		}
	}

	// TODO: ParsedTower or just the prototype name. . . . . 
	void EntityFactory::spawnTowerEntityFromPrototype(const sf::Vector2u& _tilePosition, const ParsedTower& _prototype) {
		const float scale = m_ConfigurationManager.getGameViewScale();
		sf::Texture& texture = m_TextureManager.getTexture(_prototype.animationName);
		const float offset = texture.getSize().y / 2.0f;

		ecs::Entity& e = m_EntityManager.addEntity(_prototype.prototypeName);
		e.addGroup(EntityGroup::GRenderable);
		e.addComponent<PositionComponent>(sf::Vector2f(static_cast<float>(_tilePosition.x) + 0.5f, static_cast<float>(_tilePosition.y) + 0.5f) * Definitions::TileSize);
		SpriteComponent& sc = e.addComponent<SpriteComponent>(texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y), scale);
		sc.flipHorizontal = false;
		sc.flipVertical = false;
		sc.visualOffset.y = offset;
	}
}
