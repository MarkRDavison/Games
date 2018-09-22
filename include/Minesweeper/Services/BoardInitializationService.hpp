#ifndef INCLUDED_MINESWEEPER_SERVICES_BOARD_INITIALIZATION_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_BOARD_INITIALIZATION_SERVICE_HPP_

#include <Minesweeper/Services/Interfaces/IBoardInitializationService.hpp>

namespace swp {

	class BoardInitializationService : public IBoardInitializationService {
	public:
		~BoardInitializationService(void) override;
		void initializeBoard(GameBoard& _gameBoard, const sf::Vector2i& _startingCell) override;
	};
	
}

#endif // INCLUDED_MINESWEEPER_SERVICES_BOARD_INITIALIZATION_SERVICE_HPP_