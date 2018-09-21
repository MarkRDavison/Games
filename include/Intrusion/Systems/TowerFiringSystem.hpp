#ifndef INCLUDED_INTRUSION_SYSTEMS_TOWER_FIRING_SYSTEM_HPP_
#define INCLUDED_INTRUSION_SYSTEMS_TOWER_FIRING_SYSTEM_HPP_

#include <functional>

#include <EntityComponentSystem/System.hpp>
#include <Intrusion/DataStructures/ParsedProjectile.hpp>

namespace itr {

	class TowerFiringSystem : public ecs::System {
	public:
		TowerFiringSystem(void);
		~TowerFiringSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager);

		std::function<void(const ParsedProjectile&, ecs::Entity *, ecs::Entity *)> projectileSpawned;
	};

}

#endif // INCLUDED_INTRUSION_SYSTEMS_TOWER_FIRING_SYSTEM_HPP_