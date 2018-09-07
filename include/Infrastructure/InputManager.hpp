#ifndef INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_
#define INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>

namespace inf {
	class InputManager {
	public:
		virtual ~InputManager(void) {}
		virtual bool isKeyPressed(sf::Keyboard::Key _key);

		virtual sf::Vector2i getWindowSize(void);

		std::function<sf::Vector2i(void)> m_GetWindowSizeCallback;
	};
}

#endif // INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_