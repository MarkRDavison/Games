#ifndef INCLUDED_INTRUSION_COMPONENTS_TOWER_TARGETING_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_TOWER_TARGETING_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <memory>

namespace itr {

	struct TowerTargetingComponent : ecs::Component {
		std::weak_ptr<ecs::Entity> target;
		float range{ 0.0f };
	};

}

#endif // INCLUDED_INTRUSION_COMPONENTS_TOWER_TARGETING_COMPONENT_HPP_