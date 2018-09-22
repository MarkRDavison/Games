#ifndef INCLUDED_MINESWEEPER_SCENES_EXIT_SCENE_HPP_
#define INCLUDED_MINESWEEPER_SCENES_EXIT_SCENE_HPP_

#include <Infrastructure/FontManager.hpp>
#include <Minesweeper/Services/Interfaces/ISceneChangeService.hpp>
#include <Infrastructure/InputManager.hpp>

namespace swp {

	class ExitScene : public inf::Scene {
	public:
		ExitScene(inf::FontManager& _fontManager, inf::InputManager& _inputManager, ISceneChangeService& _sceneChangeService);
		~ExitScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		inf::FontManager& m_FontManager;
		inf::InputManager& m_InputManager;
		ISceneChangeService& m_SceneChangeService;

		float m_Countdown{2.0f};
		sf::Text m_CountdownText;
	};

}

#endif // INCLUDED_MINESWEEPER_SCENES_EXIT_SCENE_HPP_