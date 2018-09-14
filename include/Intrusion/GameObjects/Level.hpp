#ifndef INCLUDED_INTRUSION_GAME_OBJECTS_LEVEL_HPP_
#define INCLUDED_INTRUSION_GAME_OBJECTS_LEVEL_HPP_

#include <SFML/Graphics.hpp>

#include <Infrastructure/Services/IPathSurface.hpp>

#include <Intrusion/DataStructures/LevelCell.hpp>
#include <Intrusion/DataStructures/ParsedLevel.hpp>
#include <Intrusion/Infrastructure/EntityFactory.hpp>
#include <Infrastructure/Services/IPathfindingService.hpp>
#include <Intrusion/Services/IWaveSpawnerService.hpp>
#include <Intrusion/Services/ILevelResourceService.hpp>
#include <Intrusion/Services/ITowerSpawnerService.hpp>
#include <Intrusion/Infrastructure/Interfaces/ITowerPlaceableSurface.hpp>

namespace itr {

	class Level final : public sf::Drawable, public inf::IPathSurface, public ITowerPlaceableSurface {
	public:
		Level(EntityFactory& _entityFactory, inf::IPathfindingService& _pathfindingService, IWaveSpawnerService& _waveSpawnerService, ILevelResourceService& _levelResourceService, ITowerSpawnerService& _towerSpawnerService);
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
		bool canPlacePrototype(const sf::Vector2i& _coordinates, const ParsedTower& _prototype) const override;
		bool canTraverse(const sf::Vector2u& _coordinates) const override;

		std::string getSurfaceName(void) const override { return m_Name; }

		std::vector<sf::Vector2u> getValidNeighbours(const sf::Vector2u& _coordinates) const override;

	private:
		bool m_Initialized{ false };
		unsigned m_Width{ 0u };
		unsigned m_Height{ 0u };
		std::string m_Name;
		std::vector<LevelCell> m_LevelCells;
		inf::Path m_Path{};

		ParsedLevel m_ParsedLevel;
		float m_WaveTimer{ 0.0f };

		sf::VertexArray m_Graphics{ sf::Triangles };
		sf::VertexArray m_PathGraphics{ sf::LineStrip };

		EntityFactory& m_EntityFactory;
		inf::IPathfindingService& m_PathfindingService;
		IWaveSpawnerService& m_WaveSpawnerService;
		ILevelResourceService& m_LevelResourceService;
		ITowerSpawnerService& m_TowerSpawnerService;
	};

}

#endif // INCLUDED_INTRUSION_GAME_OBJECTS_LEVEL_HPP_