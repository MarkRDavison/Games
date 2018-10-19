#ifndef INCLUDED_SOVEREIGN_SCENES_EXIT_SCENE_HPP_
#define INCLUDED_SOVEREIGN_SCENES_EXIT_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Sovereign/Services/Interfaces/ISceneChangeService.hpp>

namespace sov {

	class ExitScene : public inf::Scene {
	public:
		ExitScene(ISceneChangeService& _sceneChangeService);
		~ExitScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;

	private:
		ISceneChangeService& m_SceneChangeService;

		const float m_ExitTime{ 1.8f };
		float m_ExitTimeRemaining{ m_ExitTime };

	};

}

#endif // INCLUDED_SOVEREIGN_SCENES_EXIT_SCENE_HPP_