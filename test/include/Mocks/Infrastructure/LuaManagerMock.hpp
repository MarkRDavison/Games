#ifndef INCLUDED_MOCKS_INFRASTRUCTURE_LUA_MANAGER_MOCK_HPP_
#define INCLUDED_MOCKS_INFRASTRUCTURE_LUA_MANAGER_MOCK_HPP_

#include <Infrastructure/LuaManager.hpp>

namespace inf {
	class LuaManagerMock : public LuaManager {
	public:
		void runScriptFile(const std::string& _scriptPath) override {}
		void runScriptFile(const std::string& _scriptPath, const std::string& _scope) override {}
		void runScript(const std::string& _script) override {}
		void runScript(const std::string& _script, const std::string& _scope) override {}
		void createState(const std::string& _scope) override {}
		
	};
}

#endif // INCLUDED_MOCKS_INFRASTRUCTURE_LUA_MANAGER_MOCK_HPP_