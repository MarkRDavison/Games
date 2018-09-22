#ifndef INCLUDED_MINESWEEPER_SERVICES_BOARD_STATUS_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_BOARD_STATUS_SERVICE_HPP_

#include <Minesweeper/Services/Interfaces/IBoardStatusService.hpp>

namespace swp {

	class BoardStatusService : public IBoardStatusService {
	public:
		~BoardStatusService(void) override;

		void initialize(const sf::Vector2u& _size, unsigned _numberOfMines) override;

		unsigned getTotalMines(void) const override;
		unsigned getTotalFlaggedCells(void) const override;
		unsigned getTotalUnsureCells(void) const override;
		unsigned getTotalRevealedCells(void) const override;

		void revealCell(Cell& _cell) override;
		void flagCell(Cell& _cell) override;
		void unFlagCell(Cell& _cell) override;
		void flagCellAsUnkown(Cell& _cell) override;
		void unFlagCellAsUnkown(Cell& _cell) override;

	private:
		sf::Vector2u m_Size;
		unsigned m_NumberOfMines{0u};
		unsigned m_NumberFlaggedCells{ 0u };
		unsigned m_NumberFlaggedMines{ 0u };
		unsigned m_NumberUnsureCells{ 0u };
		unsigned m_NumberRevealedCells{ 0u };
	};

}

#endif // INCLUDED_MINESWEEPER_SERVICES_BOARD_STATUS_SERVICE_HPP_