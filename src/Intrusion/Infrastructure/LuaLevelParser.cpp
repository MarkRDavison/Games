#include <Intrusion/Infrastructure/LuaLevelParser.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {

	LuaLevelParser::LuaLevelParser(inf::LuaManager& _luaManager) :
		m_LuaManager(_luaManager) {

	}

	ParsedLevel LuaLevelParser::parseLevel(const std::string& _scriptName) {
		m_ParsedLevels.push_back(ParsedLevel());
		ParsedLevel& level = m_ParsedLevels.back();

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
				LevelCell& cell = level.levelCells[(y - 1) * level.width + (x - 1)];
				cell.empty = value == Definitions::Tile_Basic_Empty || value == Definitions::Tile_Basic_Start || value == Definitions::Tile_Basic_End;
				cell.start = value == Definitions::Tile_Basic_Start;
				cell.end = value == Definitions::Tile_Basic_End;
			}
		}

		return level;
	}

	bool LuaLevelParser::levelHasBeenParsed(const std::string& _name) const {
		const auto result = std::find_if(m_ParsedLevels.begin(), m_ParsedLevels.end(), [_name](const ParsedLevel& _level) { return _level.name == _name; });
		return result != m_ParsedLevels.end();
	}
	ParsedLevel LuaLevelParser::getLevel(const std::string& _name) const {
		const auto result = std::find_if(m_ParsedLevels.begin(), m_ParsedLevels.end(), [_name](const ParsedLevel& _level) { return _level.name == _name; });
		return *result;
	}
}
