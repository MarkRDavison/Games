#include <Infrastructure/LuaManager.hpp>

#include <iostream>

namespace inf {


	const std::string LuaManager::Name = "LuaManager";
	const std::string LuaManager::DefaultStateScope = "Default";

	int my_at_panic(lua_State* L) {
		std::cerr << sol::stack::get<std::string>(L, -1) << std::endl;
		return -1;
	}

	LuaManager::LuaManager(void) {
		m_DefaultScopeState.open_libraries(sol::lib::base);
	}


	LuaManager::~LuaManager(void) {
		/*lua_close(m_DefaultScopeState);

		for (auto& state : m_States) {
			lua_close(state.second);
		}*/ // TODO: Why does this crash things
	}


	void LuaManager::runScriptFile(const std::string& _scriptPath) {
		runScriptFile(_scriptPath, DefaultStateScope);
	}
	void LuaManager::runScriptFile(const std::string& _scriptPath, const std::string& _scope) {
		getState(_scope).script_file(_scriptPath);
	}
	void LuaManager::runScript(const std::string& _script) {
		runScript(_script, DefaultStateScope);
	}
	void LuaManager::runScript(const std::string& _script, const std::string& _scope) {
		getState(_scope).script(_script);
	}

	void LuaManager::createState(const std::string& _scope) {
		if (m_States.find(_scope) != m_States.end()) {
			throw std::runtime_error("LuaManager state already exists for scope " + _scope);
		}

		auto stateIterator = m_States.emplace(_scope, my_at_panic);
		sol::state& state = stateIterator.first->second;
		state.open_libraries(sol::lib::base);
	}

	sol::state& LuaManager::getState(const std::string& _scope) {
		if (_scope == DefaultStateScope) {
			return m_DefaultScopeState;
		}

		const std::map<std::basic_string<char>, sol::state>::iterator iterator = m_States.find(_scope);
		if (iterator != m_States.end()) {
			return (*iterator).second;
		}

		throw std::runtime_error("Could not find LuaManager state for scope " + _scope);
	}

}