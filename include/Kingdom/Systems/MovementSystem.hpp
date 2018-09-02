#ifndef INCLUDED_KINGDOM_SYSTEMS_MOVEMENT_SYSTEM_HPP_
#define INCLUDED_KINGDOM_SYSTEMS_MOVEMENT_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

namespace kdm {

	class MovementSystem : public ecs::System {
	public:
		MovementSystem(void);
		~MovementSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		void updateEntity(ecs::Entity* const _entity, float _delta) const;
	};

}

#endif // INCLUDED_KINGDOM_SYSTEMS_MOVEMENT_SYSTEM_HPP_