#ifndef INCLUDED_HURRICANE_COMPONENTS_DAMAGE_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_DAMAGE_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>
#include <string>

namespace hur {

	struct DamageComponent : ecs::Component {

		std::string damageType;
		int damageAmount;
		int damageTeam;

		DamageComponent(const std::string& _damageType, int _damageAmount, int _damageTeam) :
			damageType(_damageType),
			damageAmount(_damageAmount),
			damageTeam(_damageTeam) {
			
		}
	};
	
}

#endif // INCLUDED_HURRICANE_COMPONENTS_DAMAGE_COMPONENT_HPP_