#ifndef INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_
#define INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

namespace inf {
	class InputManager {
	public:
		virtual ~InputManager(void) {}
		virtual bool isKeyPressed(sf::Keyboard::Key _key);

		virtual sf::Vector2i getWindowSize(void);
		virtual sf::Vector2i getMousePosition(void);
		virtual sf::Vector2i getMousePositionRelativeToCenter(void);
		virtual sf::Vector2i getMousePositionRelativeToCenter(const sf::Vector2i& _eventCoordinates);
		virtual sf::Vector2f mapPixelToCoords(const sf::Vector2i& _pixel, const sf::View& _view);

		std::function<sf::Vector2i(void)> m_GetWindowSizeCallback;
		std::function<sf::Vector2i(void)> m_GetMousePositionCallback;
		std::function<sf::Vector2f(const sf::Vector2i&, const sf::View&)> m_MapPixelToCoordsCallback;
	};
}

#endif // INCLUDED_EXPEDITION_INFRASTRUCTURE_INPUT_MANAGER_HPP_