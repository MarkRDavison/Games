#ifndef INCLUDED_ARKANOID_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_ARKANOID_INFRASTRUCTURE_DEFINITIONS_HPP_

namespace ark {
	namespace Definitions {
		constexpr int WindowWidth{ 800 };
		constexpr int WindowHeight{ 600 };
		constexpr float BallRadius{ 10.f };
		constexpr float BallVelocity{ 600.f };
		constexpr float PaddleWidth{ 60.f };
		constexpr float PaddleHeight{ 20.f };
		constexpr float PaddleVelocity{ 500.f };
		constexpr float BlockWidth{ 60.f };
		constexpr float BlockHeight{ 20.f };
		constexpr int CountBlocksX{ 11 };
		constexpr int CountBlocksY{ 4 };
	}
}

#endif // INCLUDED_ARKANOID_INFRASTRUCTURE_DEFINITIONS_HPP_