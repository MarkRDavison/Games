#include <Infrastructure/InputManager.hpp>

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
}
