#ifndef INCLUDED_MINESWEEPER_SCENES_TITLE_SCENE_HPP_
#define INCLUDED_MINESWEEPER_SCENES_TITLE_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Minesweeper/Services/Interfaces/ISceneChangeService.hpp>

namespace swp {
	
	class TitleScene : public inf::Scene {
	public:
		TitleScene(inf::TextureManager& _textureManager, inf::FontManager& _fontManager, inf::InputManager& _inputManager, ISceneChangeService& _sceneChangeService);
		~TitleScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		bool handleMousePressed(void);

	private:
		inf::TextureManager& m_TextureManager;
		inf::FontManager& m_FontManager;
		inf::InputManager& m_InputManager;

		ISceneChangeService& m_SceneChangeService;

		sf::Text m_TitleText;
		sf::Text m_PlayText;
		sf::Text m_QuitText;

		bool m_PlayTextContainsMouse{ false };
		bool m_QuitTextContainsMouse{ false };
	};

}

#endif // INCLUDED_MINESWEEPER_SCENES_TITLE_SCENE_HPP_