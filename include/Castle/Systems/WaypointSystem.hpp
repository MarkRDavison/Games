#ifndef INCLUDED_CASTLE_SYSTEMS_WAYPOINT_SYSTEM_HPP_
#define INCLUDED_CASTLE_SYSTEMS_WAYPOINT_SYSTEM_HPP_

#include <Castle/Systems/System.hpp>

namespace castle {
	
	class WaypointSystem : System {
	public:
		WaypointSystem(void);

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta) const;
	};

}

#endif // INCLUDED_CASTLE_SYSTEMS_WAYPOINT_SYSTEM_HPP_