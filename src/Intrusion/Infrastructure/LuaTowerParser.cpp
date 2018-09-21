#include <Intrusion/Infrastructure/LuaTowerParser.hpp>

namespace itr {

	LuaTowerParser::LuaTowerParser(inf::LuaManager& _luaManager) :
		m_LuaManager(_luaManager) { }

	ParsedTower LuaTowerParser::parseTower(const std::string& _scriptName) {
		m_ParsedTowers.push_back(ParsedTower());
		ParsedTower& tower = m_ParsedTowers.back();

		m_LuaManager.runScriptFile(_scriptName, Definitions::TowerParseLuaStateScope);
		auto& state = m_LuaManager.getState(Definitions::TowerParseLuaStateScope);

		// TODO: Make these optional, all values should have defaults anyway
		tower.prototypeName = state["tower"]["prototype_name"];
		tower.animationName = state["tower"]["animation_name"];
		tower.size.x = state["tower"]["width"];
		tower.size.y = state["tower"]["height"];
		tower.range = state["tower"]["range"];
		tower.color.r = state["tower"]["color"]["r"];
		tower.color.g = state["tower"]["color"]["g"];
		tower.color.b = state["tower"]["color"]["b"];
		tower.cooldown = state["tower"]["cooldown"];

		sol::table resources = state["tower"]["cost"];

		for (unsigned i = 1; i <= resources.size(); ++i) {
			ResourceBundle::Resource resource{};

			resource.name = resources[i]["resource"];
			resource.amount = resources[i]["amount"];

			tower.cost.resources.push_back(resource);
		}


		return tower;
	}

	bool LuaTowerParser::towerHasBeenParsed(const std::string& _name) const {
		const auto result = std::find_if(m_ParsedTowers.begin(), m_ParsedTowers.end(),
		                                 [_name](const ParsedTower& _tower) { return _tower.prototypeName == _name; });
		return result != m_ParsedTowers.end();
	}

	ParsedTower LuaTowerParser::getTower(const std::string& _name) const {
		const auto result = std::find_if(m_ParsedTowers.begin(), m_ParsedTowers.end(),
		                                 [_name](const ParsedTower& _tower) { return _tower.prototypeName == _name; });
		return *result;
	}

	std::vector<ParsedTower> LuaTowerParser::getTowers(void) const {
		return m_ParsedTowers;
	}

}
