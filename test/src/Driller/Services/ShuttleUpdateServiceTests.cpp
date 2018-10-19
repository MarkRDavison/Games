#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/ShuttleUpdateService.hpp>
#include <Mocks/Driller/Services/ShuttleCompletionServiceMock.hpp>
#include <Mocks/Driller/Services/WorkerRecruitmentServiceMock.hpp>
#include <Mocks/Driller/Services/ShuttleCargoServiceMock.hpp>

namespace drl {
	namespace ShuttleUpdateServiceTests {
		
		struct Package {
			Package(void) :
				service(data, shuttleCompletion, shuttleCargo, workerRecruitment) {
				
			}
			ShuttleData data;
			ShuttleCompletionServiceMock shuttleCompletion;
			ShuttleCargoServiceMock shuttleCargo;
			WorkerRecruitmentServiceMock workerRecruitment;
			ShuttleUpdateService service;
		};

		TEST_CASE("update service with no shuttles does nothing", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};
			REQUIRE_NOTHROW(package.service.update(1.0f));
		}

		TEST_CASE("updating an idle shuttle sends it towards the surface", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::Idle;

			package.service.updateShuttle(instance, 0.0f);

			REQUIRE(ShuttleInstance::ShuttleState::TravellingToSurface == instance.state);
		}

		TEST_CASE("updating a shuttle heading towards the surface moves it towards its landing location", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const float Speed = Definitions::BaseShuttleSpeed;
			const sf::Vector2f ShuttleStartPosition{ -15.0f, +0.0f };
			const sf::Vector2f ShuttleLandPosition{ -5.0f, +0.0f };

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::TravellingToSurface;
			instance.position = ShuttleStartPosition;
			instance.landingPosition = ShuttleLandPosition;

			package.service.updateShuttle(instance, Delta);

			REQUIRE(ShuttleStartPosition + sf::Vector2f(Speed * Delta, 0.0f) == instance.position);
		}

		TEST_CASE("updating a shuttle so that it can reach its landing position updates its state to waiting on surface", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const float Speed = Definitions::BaseShuttleSpeed;
			const sf::Vector2f ShuttleStartPosition{ -15.0f, +0.0f };
			const sf::Vector2f ShuttleLandPosition = ShuttleStartPosition + sf::Vector2f(Speed * Delta, 0.0f);

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::TravellingToSurface;
			instance.position = ShuttleStartPosition;
			instance.landingPosition = ShuttleLandPosition;

			package.service.updateShuttle(instance, Delta);

			REQUIRE(ShuttleLandPosition == instance.position);
			REQUIRE(ShuttleInstance::ShuttleState::WaitingOnSurface == instance.state);
		}

		TEST_CASE("updating a shuttle heading away from the surface moves it towards its complete location", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const float Speed = Definitions::BaseShuttleSpeed;
			const sf::Vector2f ShuttleLandPosition{ -5.0f, +0.0f };
			const sf::Vector2f ShuttleCompletePosition{ +15.0f, +0.0f };

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::LeavingSurface;
			instance.position = ShuttleLandPosition;
			instance.completePosition = ShuttleCompletePosition;

			package.service.updateShuttle(instance, Delta);

			REQUIRE(ShuttleLandPosition + sf::Vector2f(Speed * Delta, 0.0f) == instance.position);
		}

		TEST_CASE("updating a shuttle so that it can reach its complete location updates its state to complete", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const float Speed = Definitions::BaseShuttleSpeed;
			const sf::Vector2f ShuttleLandPosition{ -5.0f, +0.0f };
			const sf::Vector2f ShuttleCompletePosition = ShuttleLandPosition + sf::Vector2f(Speed * Delta, 0.0f);

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::LeavingSurface;
			instance.position = ShuttleLandPosition;
			instance.completePosition = ShuttleCompletePosition;

			package.service.updateShuttle(instance, Delta);

			REQUIRE(ShuttleCompletePosition == instance.position);
			REQUIRE(ShuttleInstance::ShuttleState::Completed == instance.state);
		}

		TEST_CASE("updating a complete shuttle invokes the shuttle completion service", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::Completed;

			bool handleShuttleCompletedCallbackInvoked = false;
			package.shuttleCompletion.handleShuttleCompletedCallback = [&](ShuttleInstance& _shuttle) -> void {
				REQUIRE(&instance == &_shuttle);
				handleShuttleCompletedCallbackInvoked = true;
			};

			package.service.updateShuttle(instance, 0.0f);

			REQUIRE(handleShuttleCompletedCallbackInvoked);
		}

		TEST_CASE("updating a shuttle waiting on the surface decreases its loading time", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const float LoadingTime = 5.0f;
			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::WaitingOnSurface;
			instance.loadingTime = LoadingTime;

			package.service.updateShuttle(instance, Delta);

			REQUIRE(LoadingTime - Delta == instance.loadingTime);
		}

		TEST_CASE("updating a shuttle waiting on the surface sets its state to leaving surface if loading time is elapsed", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const float LoadingTime = Delta;
			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::WaitingOnSurface;
			instance.loadingTime = LoadingTime;

			package.shuttleCargo.loadShuttleWithCargoCallback.registerCallback([](ShuttleInstance&) -> void {});

			package.service.updateShuttle(instance, Delta);

			REQUIRE(ShuttleInstance::ShuttleState::LeavingSurface == instance.state);
		}

		TEST_CASE("when a shuttle lands it recruits workers", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			const float Delta = 1.0f;
			const float Speed = Definitions::BaseShuttleSpeed;
			const sf::Vector2f ShuttleStartPosition{ -15.0f, +0.0f };
			const sf::Vector2f ShuttleLandPosition = ShuttleStartPosition + sf::Vector2f(Speed * Delta, 0.0f);

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::TravellingToSurface;
			instance.position = ShuttleStartPosition;
			instance.landingPosition = ShuttleLandPosition;
			instance.capacity = 23;

			bool recruitWorkersCallbackInvoked = false;
			package.workerRecruitment.recruitWorkersCallback = [&](const ShuttleInstance& _shuttle) -> void {
				REQUIRE(instance.capacity == _shuttle.capacity);
				recruitWorkersCallbackInvoked = true;
			};

			package.service.updateShuttle(instance, Delta);

			REQUIRE(recruitWorkersCallbackInvoked);
		}

		TEST_CASE("when a shuttle goes to take off it calls the shuttle cargo service to load cargo", "[Driller][Services][ShuttleUpdateService]") {
			Package package{};

			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.state = ShuttleInstance::ShuttleState::WaitingOnSurface;

			package.shuttleCargo.loadShuttleWithCargoCallback.registerCallback([](ShuttleInstance&) -> void {});

			package.service.update(0.0f);

			REQUIRE(package.shuttleCargo.loadShuttleWithCargoCallback.isInvokedOnce());
		}
	}
}
