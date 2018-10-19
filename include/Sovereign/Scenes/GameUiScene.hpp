#ifndef INCLUDED_SOVEREIGN_SCENES_GAME_UI_SCENE_HPP_
#define INCLUDED_SOVEREIGN_SCENES_GAME_UI_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Sovereign/Core/Game.hpp>
#include <Sovereign/Services/Interfaces/ISceneChangeService.hpp>
#include <Infrastructure/Interfaces/IConfigurationManager.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InputManager.hpp>

namespace sov {

	class GameUiScene : public inf::Scene {
	public:
		GameUiScene(ISceneChangeService& _sceneChangeService, inf::FontManager& _fontManager);
		~GameUiScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;

		void log(LogLevel _level, const std::string& _log);

	private:
		ISceneChangeService& m_SceneChangeService;
		inf::FontManager& m_FontManager;

		std::vector<std::pair<float, sf::Text>> m_DebugTexts;
		unsigned m_CurrentIndex{ 0 };
		const unsigned MaxDebugText{ 10 };
		const float LogTime{ 5.0f };
	};

}

#endif // INCLUDED_SOVEREIGN_SCENES_GAME_UI_SCENE_HPP_