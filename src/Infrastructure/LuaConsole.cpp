#include <Infrastructure/LuaConsole.hpp>

namespace inf {

	const unsigned inf::LuaConsole::PreviousCommandBufferMaxSize = 10;

	LuaConsole::LuaConsole(const std::string& _luaStateScope, LuaManager& _luaManager) :
		m_LuaManager(_luaManager),
		m_LuaStateScope(_luaStateScope) {
	}

	bool LuaConsole::handleEvent(const sf::Event& _event) {
		if (!m_IsOpen) {
			return false;
		}

		if (_event.type == sf::Event::TextEntered) {
			const char c = static_cast<char>(_event.text.unicode);
			if (c != 8 && (!m_SupressNextTilde || c != '~' && c != '`')) {
				m_CurrentText += c;
			}
			return true;
		}

		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::Key::BackSpace) {
				if (_event.key.control) {
					bool passedWhitespace = false;
					while (!m_CurrentText.empty()) {
						const bool whitespace = m_CurrentText.back() == ' ';
						if (whitespace && !passedWhitespace) {
							passedWhitespace = true;
						}
						if (!whitespace && passedWhitespace) {
							break;
						}
						m_CurrentText.pop_back();
					}
					return true;
				}
				if (!m_CurrentText.empty()) {
					m_CurrentText.pop_back();
				}
				return true;
			}
			if (_event.key.code == sf::Keyboard::Key::Escape) {
				m_CurrentText.clear();
				setClosed();
				return true;
			}
			if (_event.key.code == sf::Keyboard::Key::Return) {
				executeScript(m_CurrentText);
				m_PreviousCommandBuffer[m_CurrentCommandIndex] = m_CurrentText;
				m_CurrentCommandIndex++;
				if (m_CurrentCommandIndex >= PreviousCommandBufferMaxSize) {
					m_CurrentCommandIndex = 0u;
				}
				m_CurrentText.clear();
				setClosed();
				return true;
			}
		}

		return false;
	}

	void LuaConsole::toggle(void) {
		m_IsOpen = !m_IsOpen;
	}

	void LuaConsole::setOpen(bool _suppressTilde /*= false*/) {
		m_IsOpen = true;
		m_SupressNextTilde = _suppressTilde;
	}
	void LuaConsole::setClosed(void) {
		m_IsOpen = false;
	}
	void LuaConsole::executeScript(const std::string& _script) const {
		m_LuaManager.runScript(_script, m_LuaStateScope);
		
	}
}
