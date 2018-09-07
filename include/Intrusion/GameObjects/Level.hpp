#ifndef INCLUDED_INTRUSION_GAME_OBJECTS_LEVEL_HPP_
#define INCLUDED_INTRUSION_GAME_OBJECTS_LEVEL_HPP_

#include <SFML/Graphics.hpp>

#include <Infrastructure/Services/IPathSurface.hpp>

#include <Intrusion/DataStructures/LevelCell.hpp>
#include <Intrusion/DataStructures/ParsedLevel.hpp>
#include <Intrusion/Infrastructure/EntityFactory.hpp>

namespace itr {


	class Level final : public sf::Drawable, public inf::IPathSurface {
	public:
		Level(EntityFactory& _entityFactory);
		~Level(void);

		void update(float _delta);
		bool handleEvent(const sf::Event& _event);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		const LevelCell& getCell(unsigned _x, unsigned _y) const;
		LevelCell& getCell(unsigned _x, unsigned _y);

		bool isInitialized(void) const noexcept { return m_Initialized; }
		void initialize(const ParsedLevel& _parsedLevel);
		void initializeGraphics(void);

		unsigned getWidth(void) const noexcept override { return m_Width; }
		unsigned getHeight(void) const noexcept override { return m_Height; }
		bool canTraverse(const sf::Vector2u& _coordinates) const override;

		std::string getSurfaceName(void) const override { return m_Name; }

		std::vector<sf::Vector2u> getValidNeighbours(const sf::Vector2u& _coordinates) const override;

	private:
		bool m_Initialized{ false };
		unsigned m_Width{ 0u };
		unsigned m_Height{ 0u };
		std::string m_Name;
		std::vector<LevelCell> m_LevelCells;

		sf::VertexArray m_Graphics{ sf::Triangles };

		EntityFactory& m_EntityFactory;
	};

}

#endif // INCLUDED_INTRUSION_GAME_OBJECTS_LEVEL_HPP_