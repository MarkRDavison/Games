#include <Minesweeper/Services/BoardInteractionService.hpp>
#include <Minesweeper/Services/Interfaces/IBoardInitializationService.hpp>
#include <Minesweeper/Infrastructure/Definitions.hpp>
#include <Minesweeper/GameObjects/GameBoard.hpp>
#include <iostream>

namespace swp {

	BoardInteractionService::BoardInteractionService(inf::InputManager& _inputManager, ConfigurationManager& _config, IBoardInitializationService& _boardInitializationService, IBoardStatusService& _boardStatusService) :
		m_InputManager(_inputManager),
		m_Config(_config),
		m_BoardInitializationService(_boardInitializationService),
		m_BoardStatusService(_boardStatusService) {
		
	}
	BoardInteractionService::~BoardInteractionService(void) {
		
	}


	bool BoardInteractionService::convertEventToBoardInteractionEvent(GameBoard& _gameBoard, const sf::Event& _event, BoardInteractionEvent& _boardInteractionEvent) {
		if (isDisabled()) {
			return false;
		}
		sf::Vector2i eventCoordinates;
		if (!getEventCoordinates(_event, eventCoordinates)) {
			return false;
		}
		
		const sf::Vector2f mousePosition(sf::Vector2f(eventCoordinates) / (m_Config.getGameViewScale() * Definitions::CellSize));
		const sf::Vector2i cellCoordinates(mousePosition);

		if (mousePosition.x < 0.0f || mousePosition.y < 0.0f) {
			return false;
		}

		if (cellCoordinates.x + 1 > static_cast<int>(_gameBoard.m_Size.x) ||
			cellCoordinates.y + 1 > static_cast<int>(_gameBoard.m_Size.y)) {
			return false;
		}
		
		if (_event.type == sf::Event::MouseMoved) {
			handleMouseMovedEvent(_gameBoard, _boardInteractionEvent, cellCoordinates);
		} else if (_event.type == sf::Event::MouseButtonPressed) {
			handleMousButtonPressedEvent(_event, _boardInteractionEvent, cellCoordinates);
		} else if (_event.type == sf::Event::MouseButtonReleased) {
			handleMouseButtonReleasedEvent(_gameBoard, _boardInteractionEvent, cellCoordinates);
		}

		return true;
	}

	void BoardInteractionService::handleBoardInteractionEvent(GameBoard& _gameBoard, const BoardInteractionEvent& _boardInteractionEvent) {
		switch (_boardInteractionEvent.type) {
		case BoardInteractionEvent::Type::Movement:
			handleMovementInteraction(_gameBoard, _boardInteractionEvent);
			break;
		case BoardInteractionEvent::Type::Click:
			handleClickInteraction(_gameBoard, _boardInteractionEvent, m_BoardInitializationService);
			break;
		default: 
			return;
		}
	}

	void BoardInteractionService::revealAll(GameBoard& _gameBoard, const sf::Vector2i& _deathAt) {
		if (_gameBoard.m_InteractionState.allRevealed) {
			return;
		}
		_gameBoard.m_InteractionState.allRevealed = true;
		BoardInteractionEvent event{};
		event.type = BoardInteractionEvent::Type::Click;
		event.click.type = BoardInteractionEvent::ClickEvent::ClickType::RevealEnd;
		for (int y = 0; y < static_cast<int>(_gameBoard.m_Size.y); ++y) {
			for (int x = 0; x < static_cast<int>(_gameBoard.m_Size.x); ++x) {
				event.click.cell.x = x;
				event.click.cell.y = y;

				Cell& c = _gameBoard.getCell({ x, y });
				
				// Set cells flagged as mines that aren't mines as false flagged
				if (c.visualState == Cell::VisualCellState::Flagged && c.actualState != Cell::CellState::Mine) {
					setCellState(_gameBoard, c, { x,y }, Cell::VisualCellState::FalseFlagged);
				} 
				// Reveals all other cells that are not correctly flagged mines
				else if (c.visualState != Cell::VisualCellState::Flagged || c.actualState != Cell::CellState::Mine) {
					revealCell(_gameBoard, c, event);
				}				
			}
		}

		if (_deathAt != Definitions::InvalidCellCoordinates) {
			Cell& c = _gameBoard.getCell(_deathAt);
			setCellState(_gameBoard, c, _deathAt, Cell::VisualCellState::TriggeredMine);
		}
	}

	void BoardInteractionService::revealWin(GameBoard& _gameBoard) {
		if (_gameBoard.m_InteractionState.gameLost) {
			return;
		}
		for (int y = 0; y < static_cast<int>(_gameBoard.m_Size.y); ++y) {
			for (int x = 0; x < static_cast<int>(_gameBoard.m_Size.x); ++x) {
				Cell& c = _gameBoard.getCell({ x, y });
				if (c.actualState == Cell::CellState::Mine) {
					setCellState(_gameBoard, c, { x, y }, Cell::VisualCellState::Flagged);
				}
			}
		}
	}

	void BoardInteractionService::setCellState(GameBoard& _gameBoard, Cell& _cell, const sf::Vector2i& _coordinates, Cell::VisualCellState _state) {
		Cell& c = _gameBoard.getCell(_coordinates);
		c.visualState = _state;
		_gameBoard.updateTextureForCell(_coordinates);
	}

	bool BoardInteractionService::isDisabled(void) {
		return m_Disabled;
	}

	void BoardInteractionService::setEnabled(bool _enabled) {
		m_Disabled = !_enabled;
	}

	bool BoardInteractionService::getEventCoordinates(const sf::Event& _event, sf::Vector2i& _coordinates) {
		if (_event.type ==  sf::Event::MouseMoved) {
			_coordinates.x = _event.mouseMove.x;
			_coordinates.y = _event.mouseMove.y;
			return true;
		}

		if (_event.type == sf::Event::MouseButtonPressed ||
			_event.type == sf::Event::MouseButtonReleased) {
			_coordinates.x = _event.mouseButton.x;
			_coordinates.y = _event.mouseButton.y;
			return true;
		}

		return false;
	}

	void BoardInteractionService::handleClickInteraction(GameBoard& _gameBoard, const BoardInteractionEvent& _boardInteractionEvent, IBoardInitializationService& _boardInitializationService) {
		_gameBoard.m_InteractionState.cycleStarted = _boardInteractionEvent.click.type == BoardInteractionEvent::ClickEvent::ClickType::CycleStart;
		_gameBoard.m_InteractionState.revealStarted = _boardInteractionEvent.click.type == BoardInteractionEvent::ClickEvent::ClickType::RevealStart;

		if (_gameBoard.m_InteractionState.cycleStarted || _gameBoard.m_InteractionState.revealStarted) {
			_gameBoard.m_InteractionState.previousInteractedCell = _boardInteractionEvent.click.cell;
			if (_gameBoard.m_InteractionState.revealStarted) {
				Cell& cell = _gameBoard.getCell(_boardInteractionEvent.click.cell);
				if (!cell.revealed) {
					setCellState(_gameBoard, cell, _boardInteractionEvent.click.cell, Cell::VisualCellState::Pressing);
				}
			} else {
				Cell& cell = _gameBoard.getCell(_boardInteractionEvent.click.cell);
				if (!cell.revealed) {
					setCellState(_gameBoard, cell, _boardInteractionEvent.click.cell, Cell::VisualCellState::Pressing);
				}
			}
		} else {
			if (_boardInteractionEvent.click.type == BoardInteractionEvent::ClickEvent::ClickType::RevealEnd) {
				Cell& cell = _gameBoard.getCell(_gameBoard.m_InteractionState.previousInteractedCell);
				if (cell.visualState == Cell::VisualCellState::Pressing) {
					if (_gameBoard.m_InteractionState.firstReveal) {
						_boardInitializationService.initializeBoard(_gameBoard, _boardInteractionEvent.click.cell);
					}
					revealRecursviceCell(_gameBoard, _boardInteractionEvent.click.cell);
				}
			}
			if (_boardInteractionEvent.click.type == BoardInteractionEvent::ClickEvent::ClickType::CycleEnd) {
				Cell& cell = _gameBoard.getCell(_gameBoard.m_InteractionState.previousInteractedCell);
				if (cell.visualState == Cell::VisualCellState::Pressing) {
					const bool wasFlagged = cell.flagged;
					const bool wasUnknown = cell.unknown;
					setCellState(_gameBoard, cell, _gameBoard.m_InteractionState.previousInteractedCell, cell.getNextCycledState());
					cell.setCurrentCycleStateFlags();
					if (cell.flagged && !wasFlagged) {
						m_BoardStatusService.flagCell(cell);
					} 
					if (!cell.flagged && wasFlagged) {
						m_BoardStatusService.unFlagCell(cell);
					}

					if (cell.unknown && !wasUnknown) {
						m_BoardStatusService.flagCellAsUnkown(cell);
					}
					if (!cell.unknown && wasUnknown) {
						m_BoardStatusService.unFlagCellAsUnkown(cell);
					}
				}
			}
			_gameBoard.m_InteractionState.previousInteractedCell = Definitions::InvalidCellCoordinates;
		}
	}

	void BoardInteractionService::handleMovementInteraction(GameBoard& _gameBoard, const BoardInteractionEvent& _boardInteractionEvent) {
		if (_gameBoard.m_InteractionState.previousInteractedCell != Definitions::InvalidCellCoordinates &&
			_boardInteractionEvent.movement.cell != Definitions::InvalidCellCoordinates &&
			_gameBoard.m_InteractionState.previousInteractedCell != _boardInteractionEvent.movement.cell) {

			// Undo temporary thing on prevCell
			Cell& prevCell = _gameBoard.getCell(_gameBoard.m_InteractionState.previousInteractedCell);
			if (!prevCell.revealed && !prevCell.flagged) {
				setCellState(_gameBoard, prevCell, _gameBoard.m_InteractionState.previousInteractedCell, Cell::VisualCellState::Unrevealed);
			} 

			Cell& cell = _gameBoard.getCell(_boardInteractionEvent.movement.cell);
			if (!cell.revealed && !cell.flagged) {
				setCellState(_gameBoard, cell, _boardInteractionEvent.movement.cell, Cell::VisualCellState::Pressing);
			}

			_gameBoard.m_InteractionState.previousInteractedCell = _boardInteractionEvent.movement.cell;
			
		}
		_gameBoard.m_InteractionState.lastMovementEventCell = _boardInteractionEvent.movement.cell;
	}

	void BoardInteractionService::handleMouseMovedEvent(GameBoard& _gameBoard, BoardInteractionEvent& _boardInteractionEvent, const sf::Vector2i cellCoordinates) {
		if (_gameBoard.m_InteractionState.lastMovementEventCell == cellCoordinates) {
			return;
		}
		_boardInteractionEvent.type = BoardInteractionEvent::Type::Movement;
		_boardInteractionEvent.movement.cell = cellCoordinates;
	}

	void BoardInteractionService::handleMousButtonPressedEvent(const sf::Event& _event, BoardInteractionEvent& _boardInteractionEvent, const sf::Vector2i _cellCoordinates) {
		_boardInteractionEvent.type = BoardInteractionEvent::Type::Click;
		_boardInteractionEvent.click.cell = _cellCoordinates;
		if (_event.mouseButton.button == sf::Mouse::Left) {
			_boardInteractionEvent.click.type = BoardInteractionEvent::ClickEvent::ClickType::RevealStart;
			if (m_BoardStatusService.onPress) {
				m_BoardStatusService.onPress();
			}
		}
		else if (_event.mouseButton.button == sf::Mouse::Right) {
			_boardInteractionEvent.click.type = BoardInteractionEvent::ClickEvent::ClickType::CycleStart;
		}
	}

	void BoardInteractionService::handleMouseButtonReleasedEvent(GameBoard& _gameBoard, BoardInteractionEvent& _boardInteractionEvent, const sf::Vector2i _cellCoordinates) {
		_boardInteractionEvent.type = BoardInteractionEvent::Type::Click;
		_boardInteractionEvent.click.cell = _cellCoordinates;
		if (_gameBoard.m_InteractionState.revealStarted) {
			_boardInteractionEvent.click.type = BoardInteractionEvent::ClickEvent::ClickType::RevealEnd;
			if (m_BoardStatusService.onRelease) {
				m_BoardStatusService.onRelease();
			}
		}
		else if (_gameBoard.m_InteractionState.cycleStarted) {
			_boardInteractionEvent.click.type = BoardInteractionEvent::ClickEvent::ClickType::CycleEnd;
		}
	}

	bool BoardInteractionService::revealCell(GameBoard& _gameBoard, Cell& _cell, const BoardInteractionEvent& _boardInteractionEvent) {
		if (!_cell.revealed) {
			m_BoardStatusService.revealCell(_cell);
		}
		_cell.revealed = true;
		if (_cell.actualState == Cell::CellState::Empty) {
			setCellState(_gameBoard, _cell, _boardInteractionEvent.click.cell, _cell.neighbouringMines > 0 ? Cell::VisualCellState::EmptyNeighbour : Cell::VisualCellState::Empty);
			return true;
		}
		if (_cell.visualState != Cell::VisualCellState::TriggeredMine) {
			setCellState(_gameBoard, _cell, _boardInteractionEvent.click.cell, Cell::VisualCellState::Mine);
		}
		return false;
	}

	void BoardInteractionService::revealRecursviceCell(GameBoard& _gameBoard, const sf::Vector2i& _coordinates) {
		Cell& cell = _gameBoard.getCell(_coordinates);
		BoardInteractionEvent event{};
		event.type = BoardInteractionEvent::Type::Click;
		event.click.cell = _coordinates;
		event.click.type = BoardInteractionEvent::ClickEvent::ClickType::RevealEnd;

		if (revealCell(_gameBoard, cell, event) && cell.neighbouringMines == 0) {
			const std::vector<sf::Vector2i>& neighbours = getValidNeighbourCoordinatesToReveal(_gameBoard, _coordinates);
			for (const sf::Vector2i& nCoord : neighbours) {
				revealRecursviceCell(_gameBoard, nCoord);
			}
		}
	}

	std::vector<sf::Vector2i> BoardInteractionService::getValidNeighbourCoordinatesToReveal(GameBoard& _gameBoard, const sf::Vector2i& _coordinates) {
		std::vector<sf::Vector2i> neighbours{};


		Cell& cell = _gameBoard.m_Cells[_coordinates.y * _gameBoard.m_Size.x + _coordinates.x];

		if (cell.actualState == Cell::CellState::Mine && cell.visualState == Cell::VisualCellState::Unrevealed) {
			return neighbours;
		}

		if (_coordinates.y > 0 && _coordinates.x > 0) {
			// Top Left Neighbour
			const sf::Vector2i n{ _coordinates.x - 1 , _coordinates.y - 1 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}
		if (_coordinates.y > 0) {
			// Top Neighbour
			const sf::Vector2i n{ _coordinates.x + 0, _coordinates.y - 1 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}
		if (_coordinates.y > 0 && _coordinates.x + 1 < static_cast<int>(_gameBoard.m_Size.x)) {
			// Top Right Neighbour
			const sf::Vector2i n{ _coordinates.x + 1, _coordinates.y - 1 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}


		if (_coordinates.x > 0) {
			// Middle Left Neighbour
			const sf::Vector2i n{ _coordinates.x - 1, _coordinates.y + 0 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}
		if (_coordinates.x + 1 < static_cast<int>(_gameBoard.m_Size.x)) {
			// Middle Right Neighbour
			const sf::Vector2i n{ _coordinates.x + 1, _coordinates.y + 0 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}


		if (_coordinates.y + 1 < static_cast<int>(_gameBoard.m_Size.y) && _coordinates.x > 0) {
			// Bottom Left Neighbour
			const sf::Vector2i n{ _coordinates.x - 1, _coordinates.y + 1 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}
		if (_coordinates.y + 1 < static_cast<int>(_gameBoard.m_Size.y)) {
			// Bottom Neighbour
			const sf::Vector2i n{ _coordinates.x + 0, _coordinates.y + 1 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}
		if (_coordinates.y + 1 < static_cast<int>(_gameBoard.m_Size.y) && _coordinates.x + 1 < static_cast<int>(_gameBoard.m_Size.x)) {
			// Bottom Left Neighbour
			const sf::Vector2i n{ _coordinates.x + 1, _coordinates.y + 1 };
			Cell& nCell = _gameBoard.getCell(n);
			if (isCellValidForFirstClick(nCell)) {
				neighbours.push_back(n);
			}
		}

		return neighbours;
	}

	bool BoardInteractionService::isCellValidForFirstClick(Cell& _cell) {
		return _cell.visualState == Cell::VisualCellState::Unrevealed && _cell.actualState != Cell::CellState::Mine;
	}
}
