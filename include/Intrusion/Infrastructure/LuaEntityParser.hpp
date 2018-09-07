#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_ENTITY_PARSER_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_ENTITY_PARSER_HPP_

#include <Infrastructure/LuaManager.hpp>
#include <Intrusion/DataStructures/ParsedEntity.hpp>

namespace itr {

	class LuaEntityParser {
	public:
		LuaEntityParser(inf::LuaManager& _luaManager);

		ParsedEntity parseEntity(const std::string& _scriptName);

		bool entityHasBeenParsed(const std::string& _name) const;
		ParsedEntity getEntity(const std::string& _name) const;

	private:
		inf::LuaManager& m_LuaManager;
		std::vector<ParsedEntity> m_ParsedEntities;
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_ENTITY_PARSER_HPP_