#ifndef INCLUDED_INTRUSION_SYSTEMS_PROJECTILE_CONTROL_SYSTEM_HPP_
#define INCLUDED_INTRUSION_SYSTEMS_PROJECTILE_CONTROL_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

namespace itr {
	
	class ProjectileControlSystem : public ecs::System {
	public:
		ProjectileControlSystem(void);
		~ProjectileControlSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager);
	};

}

#endif // INCLUDED_INTRUSION_SYSTEMS_PROJECTILE_CONTROL_SYSTEM_HPP_