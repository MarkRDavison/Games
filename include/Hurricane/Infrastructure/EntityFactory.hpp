#ifndef INCLUDED_HURRICANE_INFRASTRUCTURE_ENTITY_FACTORY_HPP_
#define INCLUDED_HURRICANE_INFRASTRUCTURE_ENTITY_FACTORY_HPP_

#include <Hurricane/Infrastructure/LuaDataParser.hpp>

#include <Infrastructure/TextureManager.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/EntityManager.hpp>

namespace hur {

	class EntityFactory {
	public:
		EntityFactory(inf::TextureManager& _textureManager, LuaDataParser& _luaDataParser);
		~EntityFactory(void);

		ecs::Entity& createPlayer(ecs::EntityManager& _entityManager) const;
		ecs::Entity& createBlackEnemy(ecs::EntityManager& _entityManager, int _index, const sf::Vector2f& _position) const;
		ecs::Entity& createBolt(ecs::EntityManager& _entityManager, const std::string& _bolt, const sf::Vector2f& _position) const;
		ecs::Entity& createPill(ecs::EntityManager& _entityManager, const std::string& _pill, const sf::Vector2f& _position) const;

		void createPotentialDropFromDropTable(ecs::EntityManager& _entityManager, const std::string& _dropTable, const sf::Vector2f& _position) const;
		

	private:
		inf::TextureManager& m_TextureManager;
		LuaDataParser& m_LuaDataParser;
	};
	
}

#endif // INCLUDED_HURRICANE_INFRASTRUCTURE_ENTITY_FACTORY_HPP_