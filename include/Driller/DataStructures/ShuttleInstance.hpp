#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_INSTANCE_HPP_

#include <Driller/Infrastructure/Definitions.hpp>
#include <Driller/DataStructures/ShuttlePrototype.hpp>
#include <Infrastructure/DataStructures/ResourceBundle.hpp>

namespace drl {

	struct ShuttleInstance {
		enum class ShuttleState {
			Idle,
			TravellingToSurface,
			WaitingOnSurface,
			LeavingSurface,
			Completed
		};

		EntityId Id;
		ShuttlePrototypeId prototypeId;
		ShuttleState state{ ShuttleState::Idle };
		float loadingTime{ 0.0f };
		bool removalRequired{ false };
		int capacity{ 1 };
		sf::Vector2f position;
		sf::Vector2f landingPosition;
		sf::Vector2f completePosition;
		inf::ResourceBundle cargo;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_INSTANCE_HPP_