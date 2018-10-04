#ifndef INCLUDED_DRILLER_SCENES_GAME_UI_SCENE_HPP_
#define INCLUDED_DRILLER_SCENES_GAME_UI_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Driller/Services/Interfaces/ISceneChangeService.hpp>
#include <Driller/Services/Interfaces/IGameCommandService.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/Services/ResourceService.hpp>

namespace drl {

	class GameUiScene : public inf::Scene {
	public:
		GameUiScene(ISceneChangeService& _sceneChangeService, inf::FontManager& _fontManager, inf::ResourceService& _resourceService, IGameCommandService& _gameCommandService);
		~GameUiScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;

		void updateResourceText(const std::string& _resourceName);

	private:
		ISceneChangeService& m_SceneChangeService;
		inf::FontManager& m_FontManager;
		inf::ResourceService& m_ResourceService;
		IGameCommandService& m_GameCommandService;

		std::map<std::string, sf::Text> m_ResourceTexts;
	};

}

#endif // INCLUDED_DRILLER_SCENES_GAME_UI_SCENE_HPP_