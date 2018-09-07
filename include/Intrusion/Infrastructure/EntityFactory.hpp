#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_FACTORY_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_FACTORY_HPP_

#include <EntityComponentSystem/EntityManager.hpp>
#include "LuaEntityParser.hpp"
#include <Infrastructure/TextureManager.hpp>
#include "IntrusionConfigurationManager.hpp"

namespace itr {
	
	class EntityFactory {
	public:
		EntityFactory(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager, IntrusionConfigurationManager& _configurationManager, LuaEntityParser& _luaEntityParser);
		~EntityFactory(void);

		void spawnWaveEntityFromPrototype(const sf::Vector2u& _tilePosition, const std::string& _prototype);

	private:
		inf::TextureManager& m_TextureManager;
		ecs::EntityManager& m_EntityManager;
		IntrusionConfigurationManager& m_ConfigurationManager;
		LuaEntityParser& m_LuaEntityParser;
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_FACTORY_HPP_