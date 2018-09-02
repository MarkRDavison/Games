#include <Kingdom/GameObjects/Level.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>
#include <cassert>

namespace kdm {
	
	Level::Level(void) {
		
	}
	Level::~Level(void) {
		
	}

	void Level::update(float _delta) {
		
	}
	bool Level::handleEvent(const sf::Event& _event) {
		return false;
	}
	void Level::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		_target.draw(m_Graphics, _states);
	}

	const LevelCell& Level::getCell(unsigned _x, unsigned _y) const {
		assert(_x < m_Width);
		assert(_y < m_Height);

		return m_LevelCells[_y * m_Width + _x];
	}
	LevelCell& Level::getCell(unsigned _x, unsigned _y) {
		assert(_x < m_Width);
		assert(_y < m_Height);

		return m_LevelCells[_y * m_Width + _x];
	}

	void Level::initialize(const ParsedLevel& _parsedLevel) {
		m_Width = _parsedLevel.width;
		m_Height = _parsedLevel.height;
		m_Name = _parsedLevel.name;
		m_Initialized = true;

		m_LevelCells = std::vector<LevelCell>(_parsedLevel.levelCells);
	}

	void Level::initializeGraphics(void) {
		m_Graphics.clear();
		m_Graphics = sf::VertexArray(sf::Triangles, m_Width * m_Height * 6);
		for (unsigned y = 0u; y < m_Height; ++y) {
			for (unsigned x = 0u; x < m_Width; ++x) {

				const sf::Color col = m_LevelCells[y * m_Width + x].empty
					? sf::Color::Green
					: sf::Color::Red;

				m_Graphics[(y * m_Width + x) * 6 + 0] = sf::Vertex(sf::Vector2f(Definitions::TileSize * static_cast<float>(x + 0), Definitions::TileSize * static_cast<float>(y + 0)), col, sf::Vector2f(0.0f, 0.0f));
				m_Graphics[(y * m_Width + x) * 6 + 1] = sf::Vertex(sf::Vector2f(Definitions::TileSize * static_cast<float>(x + 1), Definitions::TileSize * static_cast<float>(y + 0)), col, sf::Vector2f(32.0f, 0.0f));
				m_Graphics[(y * m_Width + x) * 6 + 2] = sf::Vertex(sf::Vector2f(Definitions::TileSize * static_cast<float>(x + 1), Definitions::TileSize * static_cast<float>(y + 1)), col, sf::Vector2f(32.0f, 32.0f));

				m_Graphics[(y * m_Width + x) * 6 + 3] = sf::Vertex(sf::Vector2f(Definitions::TileSize * static_cast<float>(x + 0), Definitions::TileSize * static_cast<float>(y + 0)), col, sf::Vector2f(0.0f, 0.0f));
				m_Graphics[(y * m_Width + x) * 6 + 4] = sf::Vertex(sf::Vector2f(Definitions::TileSize * static_cast<float>(x + 1), Definitions::TileSize * static_cast<float>(y + 1)), col, sf::Vector2f(32.0f, 32.0f));
				m_Graphics[(y * m_Width + x) * 6 + 5] = sf::Vertex(sf::Vector2f(Definitions::TileSize * static_cast<float>(x + 0), Definitions::TileSize * static_cast<float>(y + 1)), col, sf::Vector2f(0.0f, 32.0f));
			}
		}
	}

	bool Level::canTraverse(const sf::Vector2u& _coordinates) const {
		return getCell(_coordinates.x, _coordinates.y).empty;
	}

	std::vector<sf::Vector2u> Level::getValidNeighbours(const sf::Vector2u& _coordinates) const {
		std::vector<sf::Vector2u> neighbours{};

		if (_coordinates.x > 0) {
			// left
			neighbours.push_back(sf::Vector2u(_coordinates.x - 1, _coordinates.y));
		}
		if (_coordinates.y > 0) {
			// top
			neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y - 1));
		}
		if (_coordinates.x < m_Width - 1) {
			// right
			neighbours.push_back(sf::Vector2u(_coordinates.x + 1, _coordinates.y));
		}
		if (_coordinates.y < m_Height - 1) {
			// bottom
			neighbours.push_back(sf::Vector2u(_coordinates.x, _coordinates.y + 1));
		}

		return neighbours;
	}

}
