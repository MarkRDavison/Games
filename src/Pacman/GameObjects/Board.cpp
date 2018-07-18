#include <Pacman/GameObjects/Board.hpp>

#define TILE_GAP 0.05f

namespace pacman {

	sf::Color colorFromCell(const BoardCell& _cell) {
		if (_cell.isOpen) {
			return sf::Color::Green;
		}
		return sf::Color::Red;
	}

	Board::Board(void) :
		width(0u),
		height(0u),
		m_VertexArray(sf::Triangles) {
		
	}
	Board::~Board(void) {
		
	}

	void Board::update(float _delta) {
		
	}
	void Board::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		_target.draw(m_VertexArray, _states);
	}

	void Board::initialize() {
		m_VertexArray.clear();
		for (std::size_t y =  0u; y < height; ++y) {
			for (std::size_t x = 0u; x < width; ++x) {

				const BoardCell& cell = m_BoardCells[y * width + x];
				const sf::Color col = colorFromCell(cell);

				m_VertexArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + 0u) + TILE_GAP, static_cast<float>(y + 0u) + TILE_GAP), col));
				m_VertexArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + 1u) - TILE_GAP, static_cast<float>(y + 0u) + TILE_GAP), col));
				m_VertexArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + 1u) - TILE_GAP, static_cast<float>(y + 1u) - TILE_GAP), col));

				m_VertexArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + 0u) + TILE_GAP, static_cast<float>(y + 0u) + TILE_GAP), col));
				m_VertexArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + 1u) - TILE_GAP, static_cast<float>(y + 1u) - TILE_GAP), col));
				m_VertexArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(x + 0u) + TILE_GAP, static_cast<float>(y + 1u) - TILE_GAP), col));
			}
		}
	}

	bool Board::canMove(inf::Orientation _orientation, const sf::Vector2f& _currentPosition, float& _maximum) const {
		return false;
	}

}
