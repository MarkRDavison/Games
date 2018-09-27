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

		static const sf::Color DistinctMaroon;
		static const sf::Color DistinctBrown;
		static const sf::Color DistinctOlive;
		static const sf::Color DistinctTeal;
		static const sf::Color DistinctNavy;
		static const sf::Color DistinctBlack;
		static const sf::Color DistinctRed;
		static const sf::Color DistinctOrange;
		static const sf::Color DistinctYellow;
		static const sf::Color DistinctLime;
		static const sf::Color DistinctGreen;
		static const sf::Color DistinctCyan;
		static const sf::Color DistinctBlue;
		static const sf::Color DistinctPurple;
		static const sf::Color DistinctMagenta;
		static const sf::Color DistinctGray;
		static const sf::Color DistinctPink;
		static const sf::Color DistinctApricot;
		static const sf::Color DistinctBeige;
		static const sf::Color DistinctMint;
		static const sf::Color DistinctLavender;
		static const sf::Color DistinctWhite;
	};
}

#endif // INCLUDED_EXPEDITION_UTILITY_COLOUR_HPP_