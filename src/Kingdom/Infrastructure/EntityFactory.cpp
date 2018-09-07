#include <Kingdom/Infrastructure/EntityFactory.hpp>
#include <Kingdom/Infrastructure/KingdomEntityGroups.hpp>
#include <Kingdom/Components/PositionComponent.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>
#include <Kingdom/Components/SpriteComponent.hpp>
#include <Kingdom/Components/MovementComponent.hpp>
#include <Kingdom/Components/PathfindingComponent.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>
#include <Kingdom/Components/JobPerformerComponent.hpp>

namespace kdm {

	EntityFactory::EntityFactory(ecs::EntityManager& _entityManager, inf::TextureManager& _textureManager, KingdomConfigurationManager& _configurationManager) :
		m_EntityManager(_entityManager),
		m_TextureManager(_textureManager),
		m_ConfigurationManager(_configurationManager) {
		
	}
	EntityFactory::~EntityFactory(void) {
		
	}

	ecs::Entity& EntityFactory::spawnStartingBuilding(const sf::Vector2u& _tileCoordinates) const {
		const float scale = m_ConfigurationManager.getGameViewScale();
		const sf::Vector2f size({ 64.0f, 64.0f });
		const float offset = (size.y - scale) / 2;

		ecs::Entity& e = m_EntityManager.addEntity("MainBuilding");
		e.addGroup(EntityGroup::GRenderable);
		e.addComponent<PositionComponent>(sf::Vector2f(_tileCoordinates) * Definitions::TileSize + sf::Vector2f(Definitions::TileSize / 2.0f, Definitions::TileSize));
		e.addComponent<SpriteComponent>(
			m_TextureManager.getTexture(Definitions::MainBaseTextureName), 
			sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)),
			scale)
		.visualOffset.y = offset;

		return e;
	}

	ecs::Entity& EntityFactory::spawnTempOre(const sf::Vector2u& _tileCoordinates) const {
		const float scale = m_ConfigurationManager.getGameViewScale();
		const sf::Vector2f size({ 64.0f, 64.0f });

		ecs::Entity& e = m_EntityManager.addEntity("TempOre_" + std::to_string(_tileCoordinates.x) + "_" + std::to_string(_tileCoordinates.y));
		e.addGroup(EntityGroup::GRenderable);
		e.addGroup(EntityGroup::GJobProvider);
		e.addComponent<PositionComponent>(sf::Vector2f(_tileCoordinates) * Definitions::TileSize + sf::Vector2f(Definitions::TileSize / 2.0f, Definitions::TileSize));
		e.addComponent<SpriteComponent>(
			m_TextureManager.getTexture(Definitions::TempOreTextureName),
			sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)),
			scale);

		return e;
	}

	ecs::Entity& EntityFactory::spawnWorker(const sf::Vector2u& _tileCoordinates) const {
		const float scale = m_ConfigurationManager.getGameViewScale();
		const sf::Vector2f size({ 48.0f, 48.0f });
		const float offset = (size.y - scale) / 2;

		ecs::Entity& e = m_EntityManager.addEntity("Worker_" + std::to_string(_tileCoordinates.x) + "_" + std::to_string(_tileCoordinates.y));
		e.addGroup(EntityGroup::GRenderable);
		e.addGroup(EntityGroup::GMoveable);
		e.addGroup(EntityGroup::GWaypoint);
		e.addGroup(EntityGroup::GPathfindable);
		e.addGroup(EntityGroup::GJobPerformer);
		e.addComponent<PathfindingComponent>();
		e.addComponent<WaypointComponent>();
		e.addComponent<MovementComponent>().speed = 4.0f;
		e.addComponent<PositionComponent>(sf::Vector2f(_tileCoordinates) * Definitions::TileSize + sf::Vector2f(Definitions::TileSize / 2.0f, Definitions::TileSize));
		e.addComponent<JobPerformerComponent>();
		SpriteComponent& sc = e.addComponent<SpriteComponent>(
			m_TextureManager.getTexture(Definitions::WorkerTextureName),
			sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)),
			scale);
		sc.visualOffset.y = offset;
		sc.flipHorizontal = false;
		sc.flipVertical = false;

		return e;
	}

}
