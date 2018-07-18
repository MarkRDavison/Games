#ifndef INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_
#define INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_

#include <SFML/Window/Keyboard.hpp>

namespace inf {
	class InputManager {
	public:
		virtual ~InputManager(void) {}
		virtual bool isKeyPressed(sf::Keyboard::Key _key);
	};
}

#endif // INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_