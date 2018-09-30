#ifndef INCLUDED_DRILLER_SCENES_GAME_UI_SCENE_HPP_
#define INCLUDED_DRILLER_SCENES_GAME_UI_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Driller/Services/Interfaces/ISceneChangeService.hpp>
#include <Driller/Services/Interfaces/IGameCommandService.hpp>

namespace drl {

	class GameUiScene : public inf::Scene {
	public:
		GameUiScene(ISceneChangeService& _sceneChangeService, IGameCommandService& _gameCommandService);
		~GameUiScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;

	private:
		ISceneChangeService& m_SceneChangeService;
		IGameCommandService& m_GameCommandService;
	};

}

#endif // INCLUDED_DRILLER_SCENES_GAME_UI_SCENE_HPP_