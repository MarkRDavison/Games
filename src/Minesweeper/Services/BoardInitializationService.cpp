#include <Minesweeper/Services/BoardInitializationService.hpp>
#include <Minesweeper/GameObjects/GameBoard.hpp>
#include <cmath>

namespace swp {

	BoardInitializationService::~BoardInitializationService(void) {
		
	}

	void BoardInitializationService::initializeBoard(GameBoard& _gameBoard, const sf::Vector2i& _startingCell) {
		_gameBoard.m_InteractionState.firstReveal = false;
		unsigned placedMines = 0u;

		while (placedMines < _gameBoard.m_TotalMines) {
			const int x = rand() % _gameBoard.m_Size.x;
			const int y = rand() % _gameBoard.m_Size.y;

			if (std::abs(_startingCell.x - x) > 1 || std::abs(_startingCell.y - y) > 1) {

				Cell& cell = _gameBoard.m_Cells[y * _gameBoard.m_Size.x + x];
				if (cell.actualState != Cell::CellState::Mine) {
					placedMines += 1;
					cell.actualState = Cell::CellState::Mine;
				}
			}
		}

		for (unsigned y = 0; y < _gameBoard.m_Size.y; ++y) {
			for (unsigned x = 0; x < _gameBoard.m_Size.x; ++x) {
				Cell& cell = _gameBoard.m_Cells[y * _gameBoard.m_Size.x + x];

				if (cell.actualState == Cell::CellState::Mine) {
					continue;
				}

				if (y > 0 && x > 0) {
					// Top Left Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y - 1) * _gameBoard.m_Size.x + (x - 1)].actualState == Cell::CellState::Mine ? 1 : 0;
				}
				if (y > 0) {
					// Top Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y - 1) * _gameBoard.m_Size.x + (x)].actualState == Cell::CellState::Mine ? 1 : 0;
				}
				if (y > 0 && x + 1 < _gameBoard.m_Size.x) {
					// Top Right Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y - 1) * _gameBoard.m_Size.x + (x + 1)].actualState == Cell::CellState::Mine ? 1 : 0;
				}

				if (x > 0) {
					// Middle Left Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y) * _gameBoard.m_Size.x + (x - 1)].actualState == Cell::CellState::Mine ? 1 : 0;
				}

				if (x + 1 < _gameBoard.m_Size.x) {
					// Middle Right Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y) * _gameBoard.m_Size.x + (x + 1)].actualState == Cell::CellState::Mine ? 1 : 0;
				}

				if (y + 1 < _gameBoard.m_Size.y && x > 0) {
					// Bottom Left Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y + 1) * _gameBoard.m_Size.x + (x - 1)].actualState == Cell::CellState::Mine ? 1 : 0;
				}

				if (y + 1 < _gameBoard.m_Size.y) {
					// Bottom Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y + 1) * _gameBoard.m_Size.x + (x)].actualState == Cell::CellState::Mine ? 1 : 0;
				}

				if (y + 1 < _gameBoard.m_Size.y && x + 1 < _gameBoard.m_Size.x) {
					// Bottom Left Neighbour
					cell.neighbouringMines += _gameBoard.m_Cells[(y + 1) * _gameBoard.m_Size.x + (x + 1)].actualState == Cell::CellState::Mine ? 1 : 0;
				}
			}
		}
	}
}