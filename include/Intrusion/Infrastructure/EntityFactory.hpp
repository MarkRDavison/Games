#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_FACTORY_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_FACTORY_HPP_

#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/DataStructures/Path.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>
#include <Intrusion/Infrastructure/LuaEntityParser.hpp>

namespace itr {
	
	class EntityFactory {
	public:
		EntityFactory(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager, IntrusionConfigurationManager& _configurationManager, LuaEntityParser& _luaEntityParser);
		~EntityFactory(void);

		void spawnWaveEntityFromPrototype(const sf::Vector2u& _tilePosition, const std::string& _prototype, inf::Path& _path);

	private:
		inf::TextureManager& m_TextureManager;
		ecs::EntityManager& m_EntityManager;
		IntrusionConfigurationManager& m_ConfigurationManager;
		LuaEntityParser& m_LuaEntityParser;
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_FACTORY_HPP_