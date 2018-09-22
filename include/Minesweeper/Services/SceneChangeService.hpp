#ifndef INCLUDED_MINESWEEPER_SERVICES_SCENE_CHANGE_SERVICE_HPP_
#define INCLUDED_MINESWEEPER_SERVICES_SCENE_CHANGE_SERVICE_HPP_

#include <Minesweeper/Services/Interfaces/ISceneChangeService.hpp>

#include <Infrastructure/SceneManager.hpp>

namespace swp {
	class SceneChangeService : public ISceneChangeService {
	public:
		SceneChangeService(inf::SceneManager& _sceneManager);
		~SceneChangeService(void) override;

		void setExitScene(inf::Scene *_exitScene) override;
		void setTitleScene(inf::Scene *_titleScene) override;
		void changeToTitleScene(void) override;
		void changeToGameScene(void) override;
		void changeToExitScene(void) override;

	private:
		inf::SceneManager& m_SceneManager;
		inf::Scene *m_TitleScene{ nullptr };
		inf::Scene *m_ExitScene{ nullptr };
		inf::Scene *m_CurrentGameScene{ nullptr };
	};
}

#endif // INCLUDED_MINESWEEPER_SERVICES_SCENE_CHANGE_SERVICE_HPP_