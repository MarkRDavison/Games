#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_SCENE_CHANGE_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_SCENE_CHANGE_SERVICE_HPP_

#include <Sovereign/Core/Definitions.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Utility/Signal.hpp>

namespace sov {

	class ISceneChangeService {
	public:
		virtual ~ISceneChangeService(void) = 0;

		virtual Definitions::GameSceneState getSceneState(void) const = 0;
		virtual void setSceneState(Definitions::GameSceneState _sceneState) = 0;
		virtual void closeApplication(void) = 0;

		inf::Signal<inf::SceneManager&, Definitions::GameSceneState, Definitions::GameSceneState> sceneStateChanged;
		inf::Signal<> applicationClosed;
	};

	inline ISceneChangeService::~ISceneChangeService(void) = default;

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_SCENE_CHANGE_SERVICE_HPP_