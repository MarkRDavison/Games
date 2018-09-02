#ifndef INCLUDED_HURRICANE_INFRASTRUCTURE_LUA_DATA_PARSER_HPP_
#define INCLUDED_HURRICANE_INFRASTRUCTURE_LUA_DATA_PARSER_HPP_

#include <Hurricane/Objects/DropTable.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <vector>

namespace hur {

	class LuaDataParser {
	public:
		LuaDataParser(inf::LuaManager& _luaManager);

		void parseDropTables(const std::string& _scriptFile);

		bool hasDropTable(const std::string& _dropTableName) const;
		const DropTable& getDropTable(const std::string& _dropTableName) const;

	private:
		inf::LuaManager& m_LuaManager;
		std::vector<DropTable> m_ParsedDropTables;
	};
	
}

#endif // INCLUDED_HURRICANE_INFRASTRUCTURE_LUA_DATA_PARSER_HPP_