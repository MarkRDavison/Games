#ifndef INCLUDED_SOVEREIGN_DATA_STRUCTURES_MOVEABLE_ENTITY_HPP_
#define INCLUDED_SOVEREIGN_DATA_STRUCTURES_MOVEABLE_ENTITY_HPP_

#include <SFML/System/Vector2.hpp>

namespace sov {

	using EntityId = unsigned;
	
	struct MoveableEntity {
		EntityId id;

		sf::Vector2f movement;
		sf::Vector2f position;
		sf::Vector2f size;

		bool moveLeft{ false };
		bool moveRight{ false };
		bool moveUp{ false };
		bool moveDown{ false };

		float speed{ 8.0f };
		float pickupRange{ 2.0f };
		float mineRange{ 1.5f };

		bool isPlayer{ false };
		bool isPickup{ false };
		bool isMineable{ false };
		bool requiresRemoval{ false };

		bool isMining{ false };
		EntityId minedEntityId{ 0u };
		float mineTimeRemaining{ 2.0f };
	};

}

#endif // INCLUDED_SOVEREIGN_DATA_STRUCTURES_MOVEABLE_ENTITY_HPP_