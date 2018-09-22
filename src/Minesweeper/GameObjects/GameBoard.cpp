#include <Minesweeper/GameObjects/GameBoard.hpp>
#include <Minesweeper/Infrastructure/Definitions.hpp>
#include <Minesweeper/Services/Interfaces/IBoardInitializationService.hpp>
#include <iostream>

namespace swp {

	GameBoard::GameBoard(inf::TextureManager& _textureManager, IBoardInteractionService& _boardInteractionService) :
		m_TextureManager(_textureManager),
		m_BoardInteractionService(_boardInteractionService) {
		
	}
	GameBoard::~GameBoard(void) {
		
	}

	void GameBoard::initialize(const sf::Vector2u& _size, unsigned _mines) {
		m_TotalMines = _mines;
		m_Size = _size;
		m_Cells.clear();

		for (int y = 0; y < static_cast<int>(_size.y); ++y) {
			for (int x = 0; x < static_cast<int>(_size.x); ++x) {
				m_Cells.emplace_back(x, y);
			}
		}
	}
	void GameBoard::initializeGraphics(void) {
		m_Graphics.clear();
		m_Graphics = sf::VertexArray(sf::Triangles, m_Size.x * m_Size.y * 6);
		const sf::Color col(sf::Color::White);
		for (unsigned y = 0u; y < m_Size.y; ++y) {
			for (unsigned x = 0u; x < m_Size.x; ++x) {

				m_Graphics[(y * m_Size.x + x) * 6 + 0] = sf::Vertex(sf::Vector2f(Definitions::CellSize * static_cast<float>(x + 0), Definitions::CellSize * static_cast<float>(y + 0)), col, sf::Vector2f(0.0f, 0.0f));
				m_Graphics[(y * m_Size.x + x) * 6 + 1] = sf::Vertex(sf::Vector2f(Definitions::CellSize * static_cast<float>(x + 1), Definitions::CellSize * static_cast<float>(y + 0)), col, sf::Vector2f(32.0f, 0.0f));
				m_Graphics[(y * m_Size.x + x) * 6 + 2] = sf::Vertex(sf::Vector2f(Definitions::CellSize * static_cast<float>(x + 1), Definitions::CellSize * static_cast<float>(y + 1)), col, sf::Vector2f(32.0f, 32.0f));

				m_Graphics[(y * m_Size.x + x) * 6 + 3] = sf::Vertex(sf::Vector2f(Definitions::CellSize * static_cast<float>(x + 0), Definitions::CellSize * static_cast<float>(y + 0)), col, sf::Vector2f(0.0f, 0.0f));
				m_Graphics[(y * m_Size.x + x) * 6 + 4] = sf::Vertex(sf::Vector2f(Definitions::CellSize * static_cast<float>(x + 1), Definitions::CellSize * static_cast<float>(y + 1)), col, sf::Vector2f(32.0f, 32.0f));
				m_Graphics[(y * m_Size.x + x) * 6 + 5] = sf::Vertex(sf::Vector2f(Definitions::CellSize * static_cast<float>(x + 0), Definitions::CellSize * static_cast<float>(y + 1)), col, sf::Vector2f(0.0f, 32.0f));

				updateTextureForCell(sf::Vector2u(x, y));
			}
		}
	}

	void GameBoard::update(float _delta) {
		
	}
	bool GameBoard::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::F8) {
				m_BoardInteractionService.revealAll(*this, Definitions::InvalidCellCoordinates);
				return true;
			}
		}
		BoardInteractionEvent boardEvent{};
		if (m_BoardInteractionService.convertEventToBoardInteractionEvent(*this, _event, boardEvent)) {
			m_BoardInteractionService.handleBoardInteractionEvent(*this, boardEvent);
			return true;
		}

		return false;
	}
	void GameBoard::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		_states.texture = &m_TextureManager.getTexture(Definitions::CellSpriteSheetTextureName);
		_target.draw(m_Graphics, _states);
	}

	Cell& GameBoard::getCell(const sf::Vector2i& _coordinates) {
		return m_Cells[_coordinates.y * m_Size.x + _coordinates.x];
	}

	void GameBoard::updateTextureForCell(const sf::Vector2i& _coordinates) {
		updateTextureForCell(sf::Vector2u(_coordinates));
	}
	void GameBoard::updateTextureForCell(const sf::Vector2u& _coordinates) {
		Cell& cell = m_Cells[_coordinates.y * m_Size.x + _coordinates.x];
		
		sf::Vector2f textureCell{};
		if (cell.visualState == Cell::VisualCellState::Mine) {
			textureCell = { 2.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::Empty) {
			textureCell = { 1.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::Unrevealed) {
			textureCell = { 0.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::Flagged) {
			textureCell = { 3.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::FalseFlagged) {
			textureCell = { 7.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::Unsure) {
			textureCell = { 4.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::Pressing) {
			textureCell = { 5.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::TriggeredMine) {
			textureCell = { 6.0f, 0.0f };
		}
		else if (cell.visualState == Cell::VisualCellState::EmptyNeighbour) {
			const float neighbours = static_cast<float>(cell.neighbouringMines);
			textureCell = { neighbours - 1.0f, 1.0f };
		}

		m_Graphics[(_coordinates.y * m_Size.x + _coordinates.x) * 6 + 0].texCoords = sf::Vector2f((textureCell.x + 0) * 32.0f, (textureCell.y + 0) * 32.0f);
		m_Graphics[(_coordinates.y * m_Size.x + _coordinates.x) * 6 + 1].texCoords = sf::Vector2f((textureCell.x + 1) * 32.0f, (textureCell.y + 0) * 32.0f);
		m_Graphics[(_coordinates.y * m_Size.x + _coordinates.x) * 6 + 2].texCoords = sf::Vector2f((textureCell.x + 1) * 32.0f, (textureCell.y + 1) * 32.0f);

		m_Graphics[(_coordinates.y * m_Size.x + _coordinates.x) * 6 + 3].texCoords = sf::Vector2f((textureCell.x + 0) * 32.0f, (textureCell.y + 0) * 32.0f);
		m_Graphics[(_coordinates.y * m_Size.x + _coordinates.x) * 6 + 4].texCoords = sf::Vector2f((textureCell.x + 1) * 32.0f, (textureCell.y + 1) * 32.0f);
		m_Graphics[(_coordinates.y * m_Size.x + _coordinates.x) * 6 + 5].texCoords = sf::Vector2f((textureCell.x + 0) * 32.0f, (textureCell.y + 1) * 32.0f);
	}

}
