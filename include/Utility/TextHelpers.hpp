#ifndef INCLUDED_UTILITY_TEXT_HELPERS_HPP_
#define INCLUDED_UTILITY_TEXT_HELPERS_HPP_

#include <SFML/Graphics/Text.hpp>

namespace inf {
	
	class TextHelpers {
	public:
		TextHelpers(void) = delete;
		~TextHelpers(void) = delete;

		static void centerText(sf::Text& _text) {

			const sf::FloatRect textRect = _text.getLocalBounds();
			_text.setOrigin(
				textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f
			);

		}
	};

}

#endif // INCLUDED_UTILITY_TEXT_HELPERS_HPP_