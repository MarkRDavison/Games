#include <Minesweeper/Services/BoardStatusService.hpp>
#include <iostream>

namespace swp {
	
	BoardStatusService::~BoardStatusService(void) {
		
	}

	void BoardStatusService::initialize(const sf::Vector2u& _size, unsigned _numberOfMines) {
		m_Size = _size;
		m_NumberOfMines = _numberOfMines;
		m_NumberFlaggedCells = 0u;
		m_NumberFlaggedMines = 0u;
		m_NumberUnsureCells = 0u;
		m_NumberRevealedCells = 0u;
	}

	unsigned BoardStatusService::getTotalMines(void) const {
		return m_NumberOfMines;
	}
	unsigned BoardStatusService::getTotalFlaggedCells(void) const {
		return m_NumberFlaggedCells;
	}

	unsigned BoardStatusService::getTotalUnsureCells(void) const {
		return m_NumberUnsureCells;
	}

	unsigned BoardStatusService::getTotalRevealedCells(void) const {
		return m_NumberRevealedCells;
	}

	void BoardStatusService::revealCell(Cell& _cell) {
		m_NumberRevealedCells++;

		if (m_NumberRevealedCells == m_Size.x * m_Size.y - m_NumberOfMines) {
			winSignal.invoke();
		}

		if (_cell.actualState == Cell::CellState::Mine) {
			loseSignal.invoke(_cell.xy);
		}
	}

	void BoardStatusService::flagCell(Cell& _cell) {
		if (_cell.actualState == Cell::CellState::Mine) {
			m_NumberFlaggedMines++;
		}
		m_NumberFlaggedCells++;

		if (m_NumberRevealedCells == m_Size.x * m_Size.y - m_NumberOfMines) {
			winSignal.invoke();
		}
	}

	void BoardStatusService::unFlagCell(Cell& _cell) {
		if (_cell.actualState == Cell::CellState::Mine) {
			m_NumberFlaggedMines--;
		}
		m_NumberFlaggedCells--;
	}

	void BoardStatusService::flagCellAsUnkown(Cell& _cell) {
		m_NumberUnsureCells++;
	}
	void BoardStatusService::unFlagCellAsUnkown(Cell& _cell) {
		m_NumberUnsureCells--;
	}


}
