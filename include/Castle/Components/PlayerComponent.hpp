#ifndef INCLUDED_CASTLE_COMPONENTS_PLAYER_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_PLAYER_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>
#include "CollisionComponent.hpp"

namespace castle {
	struct PlayerComponent : ecs::Component {
		static constexpr float HorizontalVelocity = 6.0f;
		static constexpr float VerticalVelocity = 6.0f;
		static constexpr float JumpVelocity = -12.8f;
		static constexpr int JumpCount{ 1 };
		int jumpLeft{ JumpCount };
		bool onGround{ true };
		bool jumpLocked{ false };
		bool facingRight{ true };
		bool interacting{ false };
		bool interactingLock{ false };
		ecs::Entity* belowEntity{nullptr};
	};
}

#endif // INCLUDED_CASTLE_COMPONENTS_PLAYER_COMPONENT_HPP_