#ifndef INCLUDED_MINESWEEPER_SERVICES_BOARD_INTERACTION_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_BOARD_INTERACTION_SERVICE_HPP_

#include <Minesweeper/Services/Interfaces/IBoardInteractionService.hpp>
#include <Minesweeper/Services/Interfaces/IBoardStatusService.hpp>
#include <Minesweeper/Infrastructure/ConfigurationManager.hpp>
#include <Minesweeper/DataStructures/Cell.hpp>
#include <Infrastructure/InputManager.hpp>


namespace swp {
	class IBoardInitializationService;

	class BoardInteractionService : public IBoardInteractionService {
	public:
		BoardInteractionService(inf::InputManager& _inputManager, ConfigurationManager& _config, IBoardInitializationService& _boardInitializationService, IBoardStatusService& _boardStatusService);
		~BoardInteractionService(void) override;

		bool convertEventToBoardInteractionEvent(GameBoard& _gameBoard, const sf::Event& _event, BoardInteractionEvent& _boardInteractionEvent) override;
		void handleBoardInteractionEvent(GameBoard& _gameBoard, const BoardInteractionEvent& _boardInteractionEvent) override;
		void revealAll(GameBoard& _gameBoard, const sf::Vector2i& _deathAt) override;
		void revealWin(GameBoard& _gameBoard) override;
		void setCellState(GameBoard& _gameBoard, Cell& _cell, const sf::Vector2i& _coordinates, Cell::VisualCellState _state) override;

		bool isDisabled(void) override;
		void setEnabled(bool _enabled) override;

		static bool getEventCoordinates(const sf::Event& _event, sf::Vector2i& _coordinates);
		void handleClickInteraction(GameBoard& _gameBoard, const BoardInteractionEvent& _boardInteractionEvent, IBoardInitializationService& _boardInitializationService);
		void handleMovementInteraction(GameBoard& _gameBoard, const BoardInteractionEvent& _boardInteractionEvent);

		void handleMouseMovedEvent(GameBoard& _gameBoard, BoardInteractionEvent& _boardInteractionEvent, const sf::Vector2i _cellCoordinates);
		void handleMousButtonPressedEvent(const sf::Event& _event, BoardInteractionEvent& _boardInteractionEvent, const sf::Vector2i _cellCoordinates);
		void handleMouseButtonReleasedEvent(GameBoard& _gameBoard, BoardInteractionEvent& _boardInteractionEvent, const sf::Vector2i _cellCoordinates);

		bool revealCell(GameBoard& _gameBoard, Cell& _cell, const BoardInteractionEvent& _boardInteractionEvent);
		void revealRecursviceCell(GameBoard& _gameBoard, const sf::Vector2i& _coordinates);
		bool isCellValidForFirstClick(Cell& _cell);

		std::vector<sf::Vector2i> getValidNeighbourCoordinatesToReveal(GameBoard& _gameBoard, const sf::Vector2i& _coordinates);

	private:
		inf::InputManager& m_InputManager;
		ConfigurationManager& m_Config;
		IBoardInitializationService& m_BoardInitializationService;
		IBoardStatusService& m_BoardStatusService;
		bool m_Disabled{ false };
	};

}

#endif // INCLUDED_MINESWEEPER_SERVICES_BOARD_INTERACTION_SERVICE_HPP_