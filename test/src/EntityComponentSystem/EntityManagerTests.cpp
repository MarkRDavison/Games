#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <EntityComponentSystem/EntityManager.hpp>

namespace ecs {
	namespace EntityManagerTests {
	
		TEST_CASE("getWeakEntityRef returns a weak_ptr that expires when the entity is removed", "[EntityComponentSystem][EntityManger]") {
			EntityManager entityManager;

			Entity& e = entityManager.addEntity();
			entityManager.refresh();

			std::weak_ptr<Entity> entity_ptr = entityManager.getWeakEntityRef(&e);

			REQUIRE_FALSE(entity_ptr.expired());

			e.destroy();
			entityManager.refresh();

			REQUIRE(entity_ptr.expired());

		}

	}
}