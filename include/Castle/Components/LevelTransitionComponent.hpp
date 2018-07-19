#ifndef INCLUDED_CASTLE_COMPONENTS_LEVEL_TRANSITION_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_LEVEL_TRANSITION_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>
#include <Castle/Infrastructure/LevelTransitionCoordinator.hpp>

namespace castle {

	struct LevelTransitionComponent : ecs::Component {
		LevelTransitionCoordinator & levelTransitionCoordinator;
		std::string targetLevelName;
		sf::Vector2f targetCoordinates;
		LevelTransitionComponent(LevelTransitionCoordinator& _levelTransitionCoordinator, const std::string& _targetLevelName, const sf::Vector2f& _coordinates) :
			levelTransitionCoordinator(_levelTransitionCoordinator ),
			targetLevelName(std::string(_targetLevelName)),
			targetCoordinates(_coordinates) {
			
		}
	};

}

#endif // INCLUDED_CASTLE_COMPONENTS_LEVEL_TRANSITION_COMPONENT_HPP_