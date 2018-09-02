#ifndef INCLUDED_INFRASTRUCTURE_LUA_CONSOLE_HPP_
#define INCLUDED_INFRASTRUCTURE_LUA_CONSOLE_HPP_

#include <Infrastructure/LuaManager.hpp>

#include <SFML/Window/Event.hpp>

#include <vector>
#include <string>

namespace inf {

	// TODO: Update to SFML 2.5 and use the clipboard!
	class LuaConsole {
	public:
		static const constexpr unsigned PreviousCommandBufferMaxSize = 10;

		LuaConsole(const std::string& _luaStateScope, LuaManager& _luaManager);

		bool handleEvent(const sf::Event& _event);

		bool isOpen(void) const noexcept { return m_IsOpen; }
		void toggle(void);
		void setOpen(bool _suppressTilde = false);
		void setClosed(void);

		void executeScript(const std::string& _script) const;

		std::string getCurrentText(void) const noexcept { return m_CurrentText; }
		unsigned getCurrentCommandBufferIndex(void) const noexcept { return m_CurrentCommandIndex; }
		std::vector<std::string> getPreviousCommandBuffer(void) const noexcept { return m_PreviousCommandBuffer; }

	private:
		LuaManager& m_LuaManager;
		bool m_SupressNextTilde{ false };
		bool m_IsOpen{ false };
		unsigned m_CurrentCommandIndex{ 0u };

		std::string m_CurrentText;
		std::string m_LuaStateScope; 
		std::vector<std::string> m_PreviousCommandBuffer{ PreviousCommandBufferMaxSize };
	};
	
}

#endif // INCLUDED_INFRASTRUCTURE_LUA_CONSOLE_HPP_