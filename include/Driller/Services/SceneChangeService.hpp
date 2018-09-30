#ifndef INCLUDED_DRILLER_SERVICES_SCENE_CHANGE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SCENE_CHANGE_SERVICE_HPP_

#include <Driller/Services/Interfaces/ISceneChangeService.hpp>
#include <Infrastructure/SceneManager.hpp>

namespace drl {
	
	class SceneChangeService : public ISceneChangeService {
	public:
		SceneChangeService(inf::SceneManager& _sceneManager);
		~SceneChangeService(void) override;

		Definitions::GameSceneState getSceneState(void) const override;
		void setSceneState(Definitions::GameSceneState _sceneState) override;

		void closeApplication(void) override;

	private:
		Definitions::GameSceneState m_SceneState{ Definitions::GameSceneState::Invalid };
		inf::SceneManager& m_SceneManager;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SCENE_CHANGE_SERVICE_HPP_