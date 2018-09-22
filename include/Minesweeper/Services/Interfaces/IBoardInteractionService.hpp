#ifndef INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_INTERACTION_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_INTERACTION_SERVICE_HPP_

#include <Minesweeper/DataStructures/BoardInteractionEvent.hpp>
#include <SFML/Window/Event.hpp>
#include <Minesweeper/DataStructures/Cell.hpp>

namespace swp {
	
	class GameBoard;

	class IBoardInteractionService {
	public:
		virtual ~IBoardInteractionService(void) = 0 {}

		virtual bool convertEventToBoardInteractionEvent(GameBoard& _gameBoard, const sf::Event& _event, BoardInteractionEvent& _boardInteractionEvent) = 0;
		virtual void handleBoardInteractionEvent(GameBoard& _gameBoard, const BoardInteractionEvent& _boardInteractionEvent) = 0;
		virtual void revealAll(GameBoard& _gameBoard, const sf::Vector2i& _deathAt) = 0;
		virtual void revealWin(GameBoard& _gameBoard) = 0;
		virtual void setCellState(GameBoard& _gameBoard, Cell& _cell, const sf::Vector2i& _coordinates, Cell::VisualCellState _state) = 0;

		virtual bool isDisabled(void) = 0;
		virtual void setEnabled(bool _enabled) = 0;
	};

}

#endif // INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_BOARD_INTERACTION_SERVICE_HPP_