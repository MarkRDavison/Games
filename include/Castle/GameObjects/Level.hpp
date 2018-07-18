#ifndef INCLUDED_CASTLE_GAME_OBJECTS_LEVEL_HPP_
#define INCLUDED_CASTLE_GAME_OBJECTS_LEVEL_HPP_

#include <Castle/DataStructures/LevelCell.hpp>
#include <Castle/Infrastructure/EntityPrototypeFactory.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>

namespace sf {
	class Event;
}

namespace castle {
	struct ParsedLevel;

	class Level final : public sf::Drawable {
	public:
		Level(void);
		~Level(void);

		void initialize(const ParsedLevel& _parsedLevel, EntityPrototypeFactory& _entityPrototypeFactory);

		void update(float _delta);
		bool handleEvent(const sf::Event& _event);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		const LevelCell& getCell(unsigned _x, unsigned _y) const;
		LevelCell& getCell(unsigned _x, unsigned _y);
		
		void initializeEntities(const ParsedLevel& _parsedLevel, EntityPrototypeFactory& _entityPrototypeFactory);
		void initializeGraphics();

		ecs::EntityManager& getEntityManager(void) { return m_EntityManager; }

		bool isInitialized(void) const noexcept { return m_Initialized; } 

		std::string getName(void) const noexcept { return m_Name; }

	private:
		bool m_Initialized{ false };
		unsigned m_Width;
		unsigned m_Height;
		std::vector<LevelCell> m_LevelCells;

		ecs::EntityManager m_EntityManager;

		sf::VertexArray m_Graphics;
		std::string m_Name;
	};

}

#endif // INCLUDED_CASTLE_GAME_OBJECTS_LEVEL_HPP_