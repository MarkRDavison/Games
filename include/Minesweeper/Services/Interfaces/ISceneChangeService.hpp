#ifndef INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_SCENE_CHANGE_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_SCENE_CHANGE_SERVICE_HPP_

#include <Infrastructure/Scene.hpp>
#include <functional>

namespace swp {
	
	class ISceneChangeService {
	public:
		virtual ~ISceneChangeService(void) = default;

		virtual void setExitScene(inf::Scene *_exitScene) = 0;
		virtual void setTitleScene(inf::Scene *_titleScene) = 0;
		virtual void changeToTitleScene(void) = 0;
		virtual void changeToGameScene(void) = 0;
		virtual void changeToExitScene(void) = 0;

		std::function<void(void)> closeApplication;
		std::function<inf::Scene *(void)> createGameScene;
	};

}

#endif // INCLUDED_MINESWEEPER_SERVICES_INTERFACES_I_SCENE_CHANGE_SERVICE_HPP_