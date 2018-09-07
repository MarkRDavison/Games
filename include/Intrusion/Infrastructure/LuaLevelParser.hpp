#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_LEVEL_PARSER_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_LEVEL_PARSER_HPP_

#include <Infrastructure/LuaManager.hpp>
#include <Intrusion/DataStructures/ParsedLevel.hpp>

namespace itr {

	class LuaLevelParser {
	public:
		LuaLevelParser(inf::LuaManager& _luaManager);

		ParsedLevel parseLevel(const std::string& _scriptName);

		bool levelHasBeenParsed(const std::string& _name) const;
		ParsedLevel getLevel(const std::string& _name) const;

	private:
		inf::LuaManager& m_LuaManager;
		std::vector<ParsedLevel> m_ParsedLevels;
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_LEVEL_PARSER_HPP_