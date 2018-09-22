#ifndef INCLUDED_MINESWEEPER_DATA_STRUCTURES_BOARD_INTERACTION_EVENT_HPP_
#define INCLUDED_MINESWEEPER_DATA_STRUCTURES_BOARD_INTERACTION_EVENT_HPP_

#include <SFML/System/Vector2.hpp>

namespace swp {
	
	struct BoardInteractionEvent {
		
		struct MovementEvent {
			sf::Vector2i cell;
		};
		struct ClickEvent {
			sf::Vector2i cell;
			enum class ClickType {
				RevealStart,
				RevealEnd,
				CycleStart,
				CycleEnd,

				None
			} type = ClickType::None;
		};

		enum class Type {
			Movement,
			Click,

			None
		} type = Type::None;

		union {
			MovementEvent movement;
			ClickEvent click;
		};

	};

}

#endif // INCLUDED_MINESWEEPER_DATA_STRUCTURES_BOARD_INTERACTION_EVENT_HPP_