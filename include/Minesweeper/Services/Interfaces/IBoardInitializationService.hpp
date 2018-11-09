#ifndef INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_INITIALIZATION_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_INITIALIZATION_SERVICE_HPP_

#include <SFML/System/Vector2.hpp>

namespace swp {
	class GameBoard;

	class IBoardInitializationService {
	public:
		virtual ~IBoardInitializationService(void) = 0;

		virtual void initializeBoard(GameBoard& _gameBoard, const sf::Vector2i& _startingCell) = 0;
	};

	inline IBoardInitializationService::~IBoardInitializationService(void) = default;

}

#endif // INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_INITIALIZATION_SERVICE_HPP_