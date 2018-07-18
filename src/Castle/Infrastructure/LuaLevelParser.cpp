#include <Castle/Infrastructure/LuaLevelParser.hpp>
#include <SFML/System/Vector2.hpp>

#define LUA_LEVEL_PARSER_SCOPE "castle::LuaLevelParser"

namespace castle {

	LuaLevelParser::LuaLevelParser(inf::LuaManager& _luaManager) :
		m_LuaManager(_luaManager) {

		m_LuaManager.createState(LUA_LEVEL_PARSER_SCOPE);
	}

	ParsedLevel LuaLevelParser::parseLevel(const std::string& _scriptName) const {
		ParsedLevel level{};
		
		m_LuaManager.runScriptFile(_scriptName, LUA_LEVEL_PARSER_SCOPE);
		auto& state = m_LuaManager.getState(LUA_LEVEL_PARSER_SCOPE);

		level.name = state["level"]["name"];
		level.width = state["level"]["width"];
		level.height = state["level"]["height"];
		level.levelCells.resize(level.width * level.height);


		auto& tiles = state["level"]["tiles"];

		for (unsigned y = 1; y <= level.height; ++y) {
			for (unsigned x = 1; x <= level.width; ++x) {
				const int value = tiles[y][x];
				level.levelCells[(y - 1) * level.width + (x - 1)].empty = value == 0;
			}
		}

		sol::table entities = state["level"]["entities"];
		for (unsigned i = 1; i <= entities.size(); ++i) {
			
			ParsedEntity entity{};
			entity.entityTable = entities[i];
			entity.prototype = entity.entityTable["prototype"];
			entity.size = { entity.entityTable["size"]["x"], entity.entityTable["size"]["y"] };
			entity.coordinates = { entity.entityTable["coordinates"]["x"], entity.entityTable["coordinates"]["y"] };
			entity.name = entity.prototype + "_X_" + std::to_string(entity.coordinates.x) + "_Y_" + std::to_string(entity.coordinates.y);
			level.entities.emplace_back(entity);
		}

		return level;
	}
}
