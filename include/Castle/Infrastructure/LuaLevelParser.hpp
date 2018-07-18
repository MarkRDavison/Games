#ifndef INCLUDED_CASTLE_INFRASTRUCTURE_LUA_LEVEL_PARSER_HPP_
#define INCLUDED_CASTLE_INFRASTRUCTURE_LUA_LEVEL_PARSER_HPP_

#include <Infrastructure/LuaManager.hpp>
#include <Castle/DataStructures/ParsedLevel.hpp>

namespace castle {
	
	class LuaLevelParser {
	public:
		LuaLevelParser(inf::LuaManager& _luaManager);

		ParsedLevel parseLevel(const std::string& _scriptName) const;

	private:
		inf::LuaManager& m_LuaManager;
	};

}

#endif // INCLUDED_CASTLE_INFRASTRUCTURE_LUA_LEVEL_PARSER_HPP_