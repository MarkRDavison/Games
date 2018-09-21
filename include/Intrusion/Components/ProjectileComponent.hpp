#ifndef INCLUDED_INTRUSION_COMPONENTS_PROJECTILE_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_PROJECTILE_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <Intrusion/DataStructures/LifeBundle.hpp>

namespace itr {
	
	struct ProjectileComponent : ecs::Component {
		std::weak_ptr<ecs::Entity> target;
		std::weak_ptr<ecs::Entity> source;

		LifeBundle damage;
	};

}

#endif // INCLUDED_INTRUSION_COMPONENTS_PROJECTILE_COMPONENT_HPP_