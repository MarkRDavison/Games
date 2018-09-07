#ifndef INCLUDED_KINGDOM_INFRASTRUCTURE_ENTITY_FACTORY_HPP_
#define INCLUDED_KINGDOM_INFRASTRUCTURE_ENTITY_FACTORY_HPP_

#include <EntityComponentSystem/EntityManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/ConfigurationManager.hpp>
#include "KingdomConfigurationManager.hpp"

namespace kdm {

	class EntityFactory {
	public:
		EntityFactory(ecs::EntityManager& _entityManager, inf::TextureManager& _textureManager, KingdomConfigurationManager& _configurationManager);
		~EntityFactory(void);

		ecs::Entity& spawnStartingBuilding(const sf::Vector2u& _tileCoordinates) const;
		ecs::Entity& spawnTempOre(const sf::Vector2u& _tileCoordinates) const;
		ecs::Entity& spawnWorker(const sf::Vector2u& _tileCoordinates) const;

	private:
		ecs::EntityManager& m_EntityManager;
		inf::TextureManager& m_TextureManager;
		KingdomConfigurationManager& m_ConfigurationManager;
	};
	
}

#endif // INCLUDED_KINGDOM_INFRASTRUCTURE_ENTITY_FACTORY_HPP_