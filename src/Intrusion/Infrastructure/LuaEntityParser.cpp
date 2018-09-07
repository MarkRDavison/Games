#include <Intrusion/Infrastructure/LuaEntityParser.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {

	LuaEntityParser::LuaEntityParser(inf::LuaManager& _luaManager) :
		m_LuaManager(_luaManager) {

	}

	ParsedEntity LuaEntityParser::parseEntity(const std::string& _scriptName) {
		m_ParsedEntities.push_back(ParsedEntity());
		ParsedEntity& entity = m_ParsedEntities.back();

		m_LuaManager.runScriptFile(_scriptName, Definitions::EntityParseLuaStateScope);
		auto& state = m_LuaManager.getState(Definitions::EntityParseLuaStateScope);

		// TODO: Make these optional, all values should have defaults anyway
		entity.prototypeName = state["entity"]["prototype_name"];
		entity.animationName = state["entity"]["animation_name"];
		entity.health = state["entity"]["health"];
		entity.speed = state["entity"]["speed"];

		return entity;
	}

	bool LuaEntityParser::entityHasBeenParsed(const std::string& _name) const {
		const auto result = std::find_if(m_ParsedEntities.begin(), m_ParsedEntities.end(), [_name](const ParsedEntity& _entity) { return _entity.prototypeName == _name; });
		return result != m_ParsedEntities.end();
	}
	ParsedEntity LuaEntityParser::getEntity(const std::string& _name) const {
		const auto result = std::find_if(m_ParsedEntities.begin(), m_ParsedEntities.end(), [_name](const ParsedEntity& _entity) { return _entity.prototypeName == _name; });
		return *result;
	}
}
