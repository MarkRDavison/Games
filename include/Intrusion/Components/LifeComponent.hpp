#ifndef INCLUDED_INTRUSION_COMPONENTS_LIFE_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_LIFE_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <Intrusion/DataStructures/LifeBundle.hpp>
#include <queue>

namespace itr {
	
	struct LifeComponent : ecs::Component {
		float health;
		float armour;
		float shields;

		std::queue<LifeBundle> lifeAdjustments;
		ResourceBundle onDeathResources;
	};

}

#endif // INCLUDED_INTRUSION_COMPONENTS_LIFE_COMPONENT_HPP_