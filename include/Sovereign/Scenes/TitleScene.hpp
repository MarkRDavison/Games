#ifndef INCLUDED_SOVEREIGN_SCENES_TITLE_SCENE_HPP_
#define INCLUDED_SOVEREIGN_SCENES_TITLE_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Sovereign/Services/Interfaces/ISceneChangeService.hpp>
#include <Infrastructure/FontManager.hpp>

namespace sov {

	class TitleScene : public inf::Scene {
	public:
		TitleScene(inf::FontManager& _fontManager, ISceneChangeService& _sceneChangeService);
		~TitleScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;

	private:
		inf::FontManager& m_FontManager;
		ISceneChangeService& m_SceneChangeService;

		sf::Text m_TitleText;
		sf::Text m_PressAnyKeyToStartText;
	};

}

#endif // INCLUDED_SOVEREIGN_SCENES_TITLE_SCENE_HPP_