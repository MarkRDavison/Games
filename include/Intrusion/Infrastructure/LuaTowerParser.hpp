#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_TOWER_PARSER_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_TOWER_PARSER_HPP_

#include <Infrastructure/LuaManager.hpp>
#include <Intrusion/DataStructures/ParsedTower.hpp>

namespace itr {

	class LuaTowerParser {
	public:
		LuaTowerParser(inf::LuaManager& _luaManager);

		ParsedTower parseTower(const std::string& _scriptName);

		bool towerHasBeenParsed(const std::string& _name) const;
		ParsedTower getTower(const std::string& _name) const;
		std::vector<ParsedTower> getTowers(void) const;

	private:
		inf::LuaManager& m_LuaManager;
		std::vector<ParsedTower> m_ParsedTowers;
	};
	
}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_LUA_TOWER_PARSER_HPP_