#ifndef INCLUDED_ARKANOID_SCENES_GAME_SCENE_HPP_
#define INCLUDED_ARKANOID_SCENES_GAME_SCENE_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/EntityManager.hpp>

#include <Infrastructure/Scene.hpp>

namespace ark {
	enum ArkanoidGroup : std::size_t {
		GPaddle,
		GBrick,
		GBall
	};

	class GameScene : public inf::Scene {
	public:
		GameScene(void);
		~GameScene(void) override;
		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		template <class T1, class T2>
		static bool isIntersecting(T1& mA, T2& mB) noexcept {
			return 
				mA.right() >= mB.left() && 
				mA.left() <= mB.right() &&
				mA.bottom() >= mB.top() && 
				mA.top() <= mB.bottom();
		}

		static void testCollisionPB(ecs::Entity& mPaddle, ecs::Entity& mBall) noexcept;

		void testCollisionBB(ecs::Entity& mBrick, ecs::Entity& mBall) const noexcept;

		ecs::Entity& createBall(void);
		ecs::Entity& createBrick(const sf::Vector2f& _position);
		ecs::Entity& createPaddle(void);

		ecs::EntityManager m_EntityManager;
	};
}

#endif // INCLUDED_ARKANOID_SCENES_GAME_SCENE_HPP_