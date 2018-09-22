#ifndef INCLUDED_MINESWEEPER_DATA_STRUCTURES_BOARD_INTERACTION_STATE_HPP_
#define INCLUDED_MINESWEEPER_DATA_STRUCTURES_BOARD_INTERACTION_STATE_HPP_

#include <Minesweeper/Infrastructure/Definitions.hpp>

namespace swp {
	
	struct BoardInteractionState {
		bool allRevealed{ false };
		bool firstReveal{ true };
		bool revealStarted{ false };
		bool cycleStarted{ false };
		bool gameLost{ false };
		sf::Vector2i lastMovementEventCell;
		sf::Vector2i previousInteractedCell{ Definitions::InvalidCellCoordinates };
	};

}

#endif // INCLUDED_MINESWEEPER_DATA_STRUCTURES_BOARD_INTERACTION_STATE_HPP_