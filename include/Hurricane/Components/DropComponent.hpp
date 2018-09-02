#ifndef INCLUDED_HURRICANE_COMPONENTS_DROP_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_DROP_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace hur {
	struct DropComponent : ecs::Component {
		std::string dropTable;

		DropComponent(const std::string& _dropTableName) :
			dropTable(_dropTableName) {
			
		}
	};
}

#endif // INCLUDED_HURRICANE_COMPONENTS_DROP_COMPONENT_HPP_