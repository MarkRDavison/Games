#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Systems/ProjectileControlSystem.hpp>
#include <Intrusion/Components/ProjectileComponent.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>
#include <Intrusion/Components/PositionComponent.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>

namespace itr {
	namespace ProjectileControlSystemTests {

		TEST_CASE("If target is still alive the path follow component gets updated to its current position", "[Intrusion][System][ProjectileControlSystem]") {
			const sf::Vector2f TargetPosition{ 5.0f, 5.0f };
			ecs::EntityManager entityManager;

			ecs::Entity& projectile = entityManager.addEntity("Projectile");
			projectile.addGroup(EntityGroup::GProjectile);
			ecs::Entity& target = entityManager.addEntity("Target");
			entityManager.refresh();

			PathFollowComponent& pfc = projectile.addComponent<PathFollowComponent>();
			pfc.pathPoints.push(sf::Vector2f());
			ProjectileComponent& pc = projectile.addComponent<ProjectileComponent>();
			pc.target = entityManager.getWeakEntityRef(&target);

			target.addComponent<PositionComponent>(TargetPosition);

			ProjectileControlSystem system;

			system.updateEntity(&projectile, 1.0f, entityManager);

			REQUIRE(TargetPosition == pfc.pathPoints.back());
		}

		TEST_CASE("If target is not still alive the path follow component gets left at its previous position", "[Intrusion][System][ProjectileControlSystem]") {
			const sf::Vector2f OriginalPosition{ 2.0f, 2.0f };
			const sf::Vector2f TargetPosition{ 5.0f, 5.0f };
			ecs::EntityManager entityManager;

			ecs::Entity& projectile = entityManager.addEntity("Projectile");
			projectile.addGroup(EntityGroup::GProjectile);
			ecs::Entity& target = entityManager.addEntity("Target");
			entityManager.refresh();

			PathFollowComponent& pfc = projectile.addComponent<PathFollowComponent>();
			pfc.pathPoints.push(OriginalPosition);
			ProjectileComponent& pc = projectile.addComponent<ProjectileComponent>();
			pc.target = entityManager.getWeakEntityRef(&target);

			target.addComponent<PositionComponent>(TargetPosition);

			target.destroy();

			entityManager.refresh();

			ProjectileControlSystem system;

			system.updateEntity(&projectile, 1.0f, entityManager);

			REQUIRE(OriginalPosition == pfc.pathPoints.back());
		}

	}
}
