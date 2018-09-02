#include <Kingdom/Infrastructure/LuaLevelParser.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>

namespace kdm {

	LuaLevelParser::LuaLevelParser(inf::LuaManager& _luaManager) :
		m_LuaManager(_luaManager) {
		
	}

	ParsedLevel LuaLevelParser::parseLevel(const std::string& _scriptName) const {
		ParsedLevel level{};

		m_LuaManager.runScriptFile(_scriptName, Definitions::LevelParseLuaStateScope);
		auto& state = m_LuaManager.getState(Definitions::LevelParseLuaStateScope);

		level.name = state["level"]["name"];
		level.width = state["level"]["width"];
		level.height = state["level"]["height"];
		level.levelCells.resize(level.width * level.height);
		
		sol::table tiles = state["level"]["tiles"];

		for (unsigned y = 1; y <= level.height; ++y) {
			for (unsigned x = 1; x <= level.width; ++x) {
				const int value = tiles[y][x];
				level.levelCells[(y - 1) * level.width + (x - 1)].empty = value == 0;
			}
		}

		return level;
	}

}
