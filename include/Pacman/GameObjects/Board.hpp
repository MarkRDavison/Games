#ifndef INCLUDED_PACMAN_GAME_OBJECTS_BOARD_HPP_
#define INCLUDED_PACMAN_GAME_OBJECTS_BOARD_HPP_

#include <SFML/Graphics.hpp>
#include <Utility/Orientation.hpp>

namespace pacman {

	struct BoardCell {

		static const char SmallPellet = '.';
		static const char LargePellet = '@';
		static const char Nothing = ' ';
		static const char Full = '#';

		BoardCell(char _character) {
			switch (_character) {
			case SmallPellet:
				isOpen = true;
				hasSmallPellet = true;
				hasLargePellet = false;
				break;
			case LargePellet:
				isOpen = true;
				hasSmallPellet = false;
				hasLargePellet = true;
				break;
			case Nothing:
				isOpen = true;
				hasSmallPellet = false;
				hasLargePellet = false;
				break;
			case Full:
				isOpen = false;
				hasSmallPellet = false;
				hasLargePellet = false;
				break;
			default:
				throw ::std::runtime_error("Invalid cell.");
			}
		}

		bool hasSmallPellet;
		bool hasLargePellet;

		bool isOpen;
	};
	
	class Board : public sf::Drawable {
	public:
		Board(void);
		~Board(void);

		void update(float _delta);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		void initialize(void);

		bool canMove(inf::Orientation _orientation, const sf::Vector2f& _currentPosition, float& _maximum) const;

		std::size_t width;
		std::size_t height;

		std::vector<BoardCell> m_BoardCells;

		sf::VertexArray m_VertexArray;

	};

}

#endif // INCLUDED_PACMAN_GAME_OBJECTS_BOARD_HPP_