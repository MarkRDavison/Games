#ifndef INCLUDED_MINESWEEPER_DATA_STRUCTURES_CELL_HPP_
#define INCLUDED_MINESWEEPER_DATA_STRUCTURES_CELL_HPP_

#include <cstdlib>
#include <SFML/System/Vector2.hpp>

namespace swp {
	
	struct Cell {

		Cell(int _x, int _y) : 
			xy(_x, _y) {
			
		}

		sf::Vector2i xy;

		enum class VisualCellState : unsigned {
			Unrevealed,
			Empty,
			EmptyNeighbour,
			Flagged,
			FalseFlagged,
			Mine,
			Unsure,
			Pressing,
			TriggeredMine
		} visualState { VisualCellState::Unrevealed };
		
		enum class CellState {
			Empty,
			Mine
		} actualState { CellState::Empty };

		int neighbouringMines{ 0 };
		bool initialized{ false };
		bool flagged{ false };
		bool revealed{ false };
		bool unknown{ false };

		Cell::VisualCellState getNextCycledState(void) const {
			if (!revealed && !flagged && !unknown) {
				return VisualCellState::Flagged;
			}

			if (!revealed && flagged && !unknown) {
				return VisualCellState::Unsure;
			}

			if (!revealed && !flagged && unknown) {
				return VisualCellState::Unrevealed;
			}

			throw std::runtime_error("Invalid state to ask to get next cycled state");
		}
		void setCurrentCycleStateFlags(void) {
			if (visualState == VisualCellState::Unrevealed) {
				revealed = false;
				flagged = false;
				unknown = false;
				return;
			}

			if (visualState == VisualCellState::Flagged) {
				revealed = false;
				flagged = true;
				unknown = false;
				return;
			}

			if (visualState == VisualCellState::Unsure) {
				revealed = false;
				flagged = false;
				unknown = true;
				return;
			}

			throw std::runtime_error("Invalid state to ask to cycled state");
		}
	};

}

#endif // INCLUDED_MINESWEEPER_DATA_STRUCTURES_CELL_HPP_