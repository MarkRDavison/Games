#ifndef INCLUDED_KINGDOM_SCENES_GAME_SCENE_HPP_
#define INCLUDED_KINGDOM_SCENES_GAME_SCENE_HPP_

#include <Kingdom/GameObjects/Level.hpp>
#include <Kingdom/Systems/RenderSystem.hpp>
#include <Kingdom/Infrastructure/EntityFactory.hpp>

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <EntityComponentSystem/EntityManager.hpp>
#include <Kingdom/Systems/MovementSystem.hpp>
#include <Kingdom/Systems/WaypointSystem.hpp>
#include <Kingdom/Systems/PathfindingSystem.hpp>

namespace kdm {
	
	class GameScene : public inf::Scene {
	public:
		GameScene(std::function<sf::Vector2f(const sf::Vector2i&)>& _convertToGameCoords, ecs::EntityManager& _entityManager, inf::TextureManager& _textureManager, EntityFactory& _entityFactory, 
			RenderSystem& _renderSystem, MovementSystem& _movementSystem, WaypointSytem& _waypointSytem, PathfindingSystem& _pathfindingSystem);
		~GameScene(void);

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

		bool handleMouseClicked(const sf::Event& _event) const;

		std::function<sf::Vector2f(const sf::Vector2i&)>& m_ScreenToGameCoords;

		Level *m_Level{nullptr};
		EntityFactory& m_EntityFactory;
		ecs::EntityManager& m_EntityManager;
		inf::TextureManager& m_TextureManager;

		RenderSystem& m_RenderSystem;
		MovementSystem& m_MovementSystem;
		WaypointSytem& m_WaypointSystem;
		PathfindingSystem& m_PathfindingSystem;
	};

}

#endif // INCLUDED_KINGDOM_SCENES_GAME_SCENE_HPP_