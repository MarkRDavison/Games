#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/SceneChangeService.hpp>

namespace drl {
	namespace SceneChangeServiceTests {

		TEST_CASE("Initial scene state is invalid", "[Driller][Service][SceneChangeService]") {
			inf::SceneManager sceneManager;
			SceneChangeService service(sceneManager);

			REQUIRE(Definitions::GameSceneState::Invalid == service.getSceneState());
		}

		TEST_CASE("Setting the scene state invokes a signal", "[Driller][Service][SceneChangeService]") {
			inf::SceneManager sceneManager;
			SceneChangeService service(sceneManager);

			bool SceneStateChangeInvoked = false;

			const int callbackId = service.sceneStateChanged.registerCallback([&](inf::SceneManager& _sceneManager, Definitions::GameSceneState _previousState, Definitions::GameSceneState _newState) {
				REQUIRE(Definitions::GameSceneState::Invalid == _previousState);
				REQUIRE(Definitions::GameSceneState::Title == _newState);
				SceneStateChangeInvoked = true;
			});

			service.setSceneState(Definitions::GameSceneState::Title);

			REQUIRE(SceneStateChangeInvoked);

			service.sceneStateChanged.unregisterCallback(callbackId);
		}

		TEST_CASE("Closing the application invokes the applicationClosed signal", "[Driller][Service][SceneChangeService]") {
			inf::SceneManager sceneManager;
			SceneChangeService service(sceneManager);

			bool CloseApplicationInvoked = false; 
			const int callbackId = service.applicationClosed.registerCallback([&](void) {
				CloseApplicationInvoked = true;
			});

			service.closeApplication();

			REQUIRE(CloseApplicationInvoked);

			service.sceneStateChanged.unregisterCallback(callbackId);
		}
	}
}