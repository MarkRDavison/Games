#ifndef INCLUDED_INTRUSION_SCENES_GAME_SCENE_HPP_
#define INCLUDED_INTRUSION_SCENES_GAME_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <Intrusion/GameObjects/Level.hpp>
#include <Intrusion/Systems/RenderSystem.hpp>
#include <Intrusion/Systems/PathFollowingSystem.hpp>

namespace itr {
	
	class GameScene : public inf::Scene {
	public:
		GameScene(inf::TextureManager& _textureManager, ecs::EntityManager& _entityManager, 
			RenderSystem& _renderSystem, PathFollowingSystem& _pathFollowingSystem);
		~GameScene(void);

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;
		Level *m_Level{ nullptr };

	private:

		inf::TextureManager& m_TextureManager;
		ecs::EntityManager& m_EntityManager;

		RenderSystem& m_RenderSystem;
		PathFollowingSystem& m_PathFollowingSystem;
	};

}

#endif // INCLUDED_INTRUSION_SCENES_GAME_SCENE_HPP_