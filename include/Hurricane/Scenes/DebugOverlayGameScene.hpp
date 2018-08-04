#ifndef INCLUDED_HURRICANE_SCENES_DEBUG_OVERLAY_GAME_SCENE_HPP_
#define INCLUDED_HURRICANE_SCENES_DEBUG_OVERLAY_GAME_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/FontManager.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <SFML/Graphics.hpp>

namespace hur {
	
	class DebugOverlayGameScene : public inf::Scene {
	public:
		DebugOverlayGameScene(ecs::EntityManager& _entityManager, inf::FontManager& _fontManager);
		~DebugOverlayGameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:
		ecs::EntityManager& m_EntityManager;
		sf::Text m_NumberOfEntitiesText;
		sf::Text m_NumberOfProjectilesText;

		const float updateRate{ 0.5f };
		float updateAccumulation{ 0.0f };
	};

}

#endif // INCLUDED_HURRICANE_SCENES_DEBUG_OVERLAY_GAME_SCENE_HPP_