#include <Minesweeper/Services/SceneChangeService.hpp>

namespace swp {

	SceneChangeService::SceneChangeService(inf::SceneManager& _sceneManager) :
		m_SceneManager(_sceneManager) {
		
	}
	SceneChangeService::~SceneChangeService(void) {

	}

	void SceneChangeService::setExitScene(inf::Scene * _exitScene) {
		m_ExitScene = _exitScene;
		m_ExitScene->setDeleteOnRemove(true);
	}

	void SceneChangeService::setTitleScene(inf::Scene *_titleScene) {
		m_TitleScene = _titleScene;
		m_TitleScene->setDeleteOnRemove(false);
	}
	void SceneChangeService::changeToTitleScene(void) {
		if (m_CurrentGameScene != nullptr) {
			m_SceneManager.removeScene(m_CurrentGameScene);
			m_CurrentGameScene = nullptr;
		}

		m_SceneManager.pushScene(m_TitleScene);
	}
	void SceneChangeService::changeToGameScene(void) {
		if (createGameScene) {
			if (m_CurrentGameScene != nullptr) {
				// We are resetting from within a game scene
				m_SceneManager.removeScene(m_CurrentGameScene);
				m_CurrentGameScene = createGameScene();
				m_CurrentGameScene->setDeleteOnRemove(true);
				m_SceneManager.pushScene(m_CurrentGameScene);
			}
			else {
				// We are starting the first one
				m_SceneManager.removeScene(m_TitleScene);
				m_CurrentGameScene = createGameScene();
				m_CurrentGameScene->setDeleteOnRemove(true);
				m_SceneManager.pushScene(m_CurrentGameScene);
			}
		}
	}

	void SceneChangeService::changeToExitScene(void) {
		if (m_CurrentGameScene != nullptr) {
			m_SceneManager.removeScene(m_CurrentGameScene);
			m_CurrentGameScene = nullptr;
		}
		m_SceneManager.removeScene(m_TitleScene);
		m_TitleScene->setDeleteOnRemove(true);
		m_SceneManager.pushScene(m_ExitScene);
	}

}