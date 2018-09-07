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

				if (cell.start) {
					level.start = { static_cast<int>(x - 1), static_cast<int>(y - 1) };
				}
				if (cell.end) {
					level.end = { static_cast<int>(x - 1), static_cast<int>(y - 1) };
				}
			}
		}

		sol::table waves = state["level"]["waves"];
		for (unsigned i = 1; i <= waves.size(); ++i) {
			sol::table wave = waves[i];

			WaveInstance instance{};
			instance.time = wave["time"];
			instance.amount = wave["amount"];
			instance.interval = wave["interval"];
			instance.entityPrototype = wave["entity_prototype"];

			level.waves.push_back(instance);
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
