#include <Driller/Services/SceneChangeService.hpp>

namespace drl {

	SceneChangeService::SceneChangeService(inf::SceneManager& _sceneManager) :
		m_SceneManager(_sceneManager) {
		
	}
	SceneChangeService::~SceneChangeService(void) {
		
	}

	Definitions::GameSceneState SceneChangeService::getSceneState(void) const {
		return m_SceneState;
	}
	void SceneChangeService::setSceneState(Definitions::GameSceneState _sceneState) {
		sceneStateChanged.invoke(m_SceneManager, m_SceneState, _sceneState);
		m_SceneState = _sceneState;
	}

	void SceneChangeService::closeApplication(void) {
		applicationClosed.invoke();
	}

}
