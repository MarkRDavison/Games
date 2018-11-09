#ifndef INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_STATUS_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_STATUS_SERVICE_HPP_

#include <Utility/Signal.hpp>
#include <Minesweeper/DataStructures/Cell.hpp>
#include <SFML/System/Vector2.hpp>

namespace swp {
	
	class IBoardStatusService {
	public:
		virtual ~IBoardStatusService(void) = 0;

		virtual void initialize(const sf::Vector2u& _size, unsigned _numberOfMines) = 0;

		virtual unsigned getTotalMines(void) const = 0;
		virtual unsigned getTotalFlaggedCells(void) const = 0;
		virtual unsigned getTotalUnsureCells(void) const = 0;
		virtual unsigned getTotalRevealedCells(void) const = 0;

		virtual void revealCell(Cell& _cell) = 0;
		virtual void flagCell(Cell& _cell) = 0;
		virtual void unFlagCell(Cell& _cell) = 0;
		virtual void flagCellAsUnkown(Cell& _cell) = 0;
		virtual void unFlagCellAsUnkown(Cell& _cell) = 0;

		inf::Signal<> winSignal;
		inf::Signal<const sf::Vector2i&> loseSignal;

		std::function<void(void)> onPress;
		std::function<void(void)> onRelease;
	};

	inline IBoardStatusService::~IBoardStatusService(void) = default;

}

#endif // INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_STATUS_SERVICE_HPP_