#ifndef INCLUDED_EXPEDITION_INFRASTRUCTURE_LUA_MANAGER_HPP_
#define INCLUDED_EXPEDITION_INFRASTRUCTURE_LUA_MANAGER_HPP_

#include <Sol2/sol.hpp>
#include <map>

namespace inf {

	class LuaManager {
	public:
		static const std::string Name;
		static const std::string DefaultStateScope;

		LuaManager(void);
		virtual ~LuaManager(void);

		virtual void runScriptFile(const std::string& _scriptPath);
		virtual void runScriptFile(const std::string& _scriptPath, const std::string& _scope);
		virtual void runScript(const std::string& _script);
		virtual void runScript(const std::string& _script, const std::string& _scope);

		virtual void createState(const std::string& _scope);

		sol::state& getState(const std::string& _scope);


		std::map<std::string, sol::state> m_States;

		sol::state m_DefaultScopeState;
	};

}

#endif // INCLUDED_EXPEDITION_INFRASTRUCTURE_LUA_MANAGER_HPP_