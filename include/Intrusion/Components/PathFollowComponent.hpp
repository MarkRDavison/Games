#ifndef INCLUDED_INTRUSION_COMPONENTS_PATH_FOLLOW_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_PATH_FOLLOW_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <functional>
#include <queue>

using PointQueue = std::queue<sf::Vector2f>;

namespace itr {
	
	struct PathFollowComponent : ecs::Component {
		
		PointQueue pathPoints;
		float speed;
		std::function<void(ecs::Entity *)> pathCompleted;

	};

}

#endif // INCLUDED_INTRUSION_COMPONENTS_PATH_FOLLOW_COMPONENT_HPP_