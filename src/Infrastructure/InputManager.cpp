#include <Infrastructure/InputManager.hpp>
#include <SFML/Window/Mouse.hpp>

namespace inf {

	bool InputManager::isKeyPressed(sf::Keyboard::Key _key) {
		return sf::Keyboard::isKeyPressed(_key);
	}

	sf::Vector2i InputManager::getWindowSize(void) {
		if (m_GetWindowSizeCallback) {
			return m_GetWindowSizeCallback();
		}

		return {};
	}

	sf::Vector2i InputManager::getMousePosition(void) {

		if (m_GetMousePositionCallback) {
			return m_GetMousePositionCallback();
		}

		return {};
	}
}
