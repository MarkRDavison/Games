#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Systems/PathFollowingSystem.hpp>
#include <Intrusion/Components/PositionComponent.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>

namespace itr {
	namespace PathFollowingSystemTests {

		TEST_CASE("Updating entity with no path to follow does nothing", "[Intrusion][System][PathFollowingSystem]") {
			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>();
			e.addComponent<PathFollowComponent>();

			PathFollowingSystem system;

			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));
		}
	}
}