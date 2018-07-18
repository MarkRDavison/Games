#ifndef INCLUDED_EXPEDITION_UTILITY_COLOUR_HPP_
#define INCLUDED_EXPEDITION_UTILITY_COLOUR_HPP_
#include <SFML/Graphics/Color.hpp>

namespace inf {
	class Colour {
		Colour(void) = delete;
		~Colour(void) = delete;
	public:


		static const sf::Color NatureGreen;
		static const sf::Color BrickRed;
		static const sf::Color Brown;
		static const sf::Color Purple;
		static const sf::Color LightGrey;
		static const sf::Color DarkGrey;
		static const sf::Color Orange;
		static const sf::Color HotPink;
	};
}

#endif // INCLUDED_EXPEDITION_UTILITY_COLOUR_HPP_