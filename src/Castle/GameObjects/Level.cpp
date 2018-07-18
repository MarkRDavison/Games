#include <Castle/GameObjects/Level.hpp>
#include <Castle/DataStructures/ParsedLevel.hpp>

#include <SFML/Graphics.hpp>

#include <cassert>

namespace castle {

	Level::Level(void) :
		m_Width(0u),
		m_Height(0u),
		m_Graphics(sf::Triangles) {
		
	}
	Level::~Level(void) {
		
	}

	void Level::initialize(const ParsedLevel& _parsedLevel, EntityPrototypeFactory& _entityPrototypeFactory) {
		m_Width = _parsedLevel.width;
		m_Height = _parsedLevel.height;
		m_Name = _parsedLevel.name;

		m_LevelCells = std::vector<LevelCell>(_parsedLevel.levelCells);
		m_Graphics = sf::VertexArray(sf::Triangles, 3 * 2 * m_Width * m_Height);
		initializeEntities(_parsedLevel, _entityPrototypeFactory);
		initializeGraphics();
		m_Initialized = true;
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

	void Level::initializeEntities(const ParsedLevel& _parsedLevel, EntityPrototypeFactory& _entityPrototypeFactory) {
		for (const ParsedEntity& parsedEntity : _parsedLevel.entities) {
			_entityPrototypeFactory.createEntityFromPrototype(m_EntityManager, parsedEntity);
		}
	}

	void Level::initializeGraphics() {
		for (unsigned y = 0u; y < m_Height; ++y) {
			for (unsigned x = 0u; x < m_Width; ++x) {

				const sf::Color col = m_LevelCells[y * m_Width + x].empty
					? sf::Color::Green
					: sf::Color::Red;

				m_Graphics[(y * m_Width + x) * 6 + 0] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 0), static_cast<float>(y + 0)), col, sf::Vector2f(0.0f, 0.0f));
				m_Graphics[(y * m_Width + x) * 6 + 1] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 1), static_cast<float>(y + 0)), col, sf::Vector2f(32.0f, 0.0f));
				m_Graphics[(y * m_Width + x) * 6 + 2] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 1), static_cast<float>(y + 1)), col, sf::Vector2f(32.0f, 32.0f));

				m_Graphics[(y * m_Width + x) * 6 + 3] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 0), static_cast<float>(y + 0)), col, sf::Vector2f(0.0f, 0.0f));
				m_Graphics[(y * m_Width + x) * 6 + 4] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 1), static_cast<float>(y + 1)), col, sf::Vector2f(32.0f, 32.0f));
				m_Graphics[(y * m_Width + x) * 6 + 5] = sf::Vertex(sf::Vector2f(static_cast<float>(x + 0), static_cast<float>(y + 1)), col, sf::Vector2f(0.0f, 32.0f));
			}
		}
	}

}
