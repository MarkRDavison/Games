#include <Infrastructure/InputManager.hpp>

namespace inf {

	bool InputManager::isKeyPressed(sf::Keyboard::Key _key) {
		return sf::Keyboard::isKeyPressed(_key);
	}
}
