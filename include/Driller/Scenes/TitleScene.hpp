#ifndef INCLUDED_DRILLER_SCENES_TITLE_SCENE_HPP_
#define INCLUDED_DRILLER_SCENES_TITLE_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Driller/Services/Interfaces/ISceneChangeService.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace drl {

	class TitleScene : public inf::Scene {
	public:
		TitleScene(inf::FontManager& _fontManager, inf::TextureManager& _textureManager, ISceneChangeService& _sceneChangeService);
		~TitleScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;

	private:
		inf::FontManager& m_FontManager;
		inf::TextureManager& m_TextureManager;
		ISceneChangeService& m_SceneChangeService;

		sf::Text m_TitleText;
		sf::Text m_PressAnyKeyToStartText;
	};

}

#endif // INCLUDED_DRILLER_SCENES_TITLE_SCENE_HPP_