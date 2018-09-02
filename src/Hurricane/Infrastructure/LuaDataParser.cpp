#include <Hurricane/Infrastructure/LuaDataParser.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Sol2/sol.hpp>

#define LUA_DATA_PARSER_SCOPE "hur::LuaDataParser"

namespace hur {

	LuaDataParser::LuaDataParser(inf::LuaManager& _luaManager) :
		m_LuaManager(_luaManager) {
		m_LuaManager.createState(LUA_DATA_PARSER_SCOPE);
	}

	void LuaDataParser::parseDropTables(const std::string& _scriptFile) {
		m_LuaManager.runScriptFile(_scriptFile, LUA_DATA_PARSER_SCOPE);
		auto& state = m_LuaManager.getState(LUA_DATA_PARSER_SCOPE);
		sol::table drop_tables = state["drop_tables"];

		for (unsigned i = 1; i <= drop_tables.size(); ++i) {

			DropTable table{};
			table.name = drop_tables[i]["name"];
			sol::table drops = drop_tables[i]["drops"];

			for (unsigned j = 1; j <= drops.size(); ++j) {
				std::pair<int, std::vector<std::string>> chanceEntities;
				chanceEntities.first = drops[j]["chance"];
				sol::table entities = drops[j]["entities"];

				for (unsigned k = 1; k <= entities.size(); ++k) {
					chanceEntities.second.push_back(entities[k]);
				}

				table.chancesAndEntities.push_back(chanceEntities);
			}

			m_ParsedDropTables.push_back(table);
		}
	}

	bool LuaDataParser::hasDropTable(const std::string& _dropTableName) const {
		return std::find_if(m_ParsedDropTables.begin(), m_ParsedDropTables.end(), [&](const DropTable& _drop) -> bool { return _drop.name == _dropTableName; }) != m_ParsedDropTables.end();
	}
	const DropTable& LuaDataParser::getDropTable(const std::string& _dropTableName) const {
		return *std::find_if(m_ParsedDropTables.begin(), m_ParsedDropTables.end(), [&](const DropTable& _drop) -> bool { return _drop.name == _dropTableName; });
	}
}