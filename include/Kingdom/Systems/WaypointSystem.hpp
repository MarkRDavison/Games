#ifndef INCLUDED_KINGDOM_SYSTEMS_WAYPOINT_SYSTEM_HPP_
#define INCLUDED_KINGDOM_SYSTEMS_WAYPOINT_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

namespace kdm {

	class WaypointSytem : public ecs::System {
	public:
		WaypointSytem(void);
		~WaypointSytem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		void updateEntity(ecs::Entity* const _entity, float _delta) const;
	};

}

#endif // INCLUDED_KINGDOM_SYSTEMS_WAYPOINT_SYSTEM_HPP_