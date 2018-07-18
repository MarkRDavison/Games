#include <Arkanoid/Scenes/GameScene.hpp>

#include <Arkanoid/Components/CircleComponent.hpp>
#include <Arkanoid/Components/PhysicsComponent.hpp>
#include <Arkanoid/Components/PlayerPaddleControlComponent.hpp>
#include <Arkanoid/Components/RectangleComponent.hpp>
#include <Arkanoid/Components/PositionComponent.hpp>

#include <Arkanoid/Infrastructure/Definitions.hpp>

#include <cmath>

namespace ark {

	GameScene::GameScene(void) :
		inf::Scene("ark::GameScene") {

		createPaddle();
		createBall();

		for (int iX{ 0 }; iX < Definitions::CountBlocksX; ++iX) {
			for (int iY{ 0 }; iY < Definitions::CountBlocksY; ++iY) {

				createBrick(sf::Vector2f{ 
					(iX + 1) * (Definitions::BlockWidth + 3) + 22,
					(iY + 2) * (Definitions::BlockHeight + 3) 
				});
			}
		}
	}
	GameScene::~GameScene(void) {

	}
	void GameScene::update(float _delta) {
		m_EntityManager.refresh();
		m_EntityManager.update(_delta);

		// We get our entities by group...
		auto& paddles(m_EntityManager.getEntitiesByGroup(ArkanoidGroup::GPaddle));
		auto& bricks(m_EntityManager.getEntitiesByGroup(ArkanoidGroup::GBrick));
		auto& balls(m_EntityManager.getEntitiesByGroup(ArkanoidGroup::GBall));

		// ...and perform collision tests on them.
		for (auto& b : balls) {
			for (auto& p : paddles) {
				testCollisionPB(*p, *b);
			}
			for (auto& br : bricks) {
				testCollisionBB(*br, *b);
			}
		}
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		m_EntityManager.draw(_target, _states);
	}
	
	void GameScene::testCollisionPB(ecs::Entity& mPaddle, ecs::Entity& mBall) noexcept 	{
		auto& cpPaddle(mPaddle.getComponent<PhysicsComponent>());
		auto& cpBall(mBall.getComponent<PhysicsComponent>());

		if (!isIntersecting(cpPaddle, cpBall)) return;

		cpBall.velocity.y = -Definitions::BallVelocity;
		if (cpBall.x() < cpPaddle.x()) {
			cpBall.velocity.x = -Definitions::BallVelocity;
		}
		else {
			cpBall.velocity.x = Definitions::BallVelocity;
		}
	}

	void GameScene::testCollisionBB(ecs::Entity& mBrick, ecs::Entity& mBall) const noexcept 	{
		auto& cpBrick(mBrick.getComponent<PhysicsComponent>());
		auto& cpBall(mBall.getComponent<PhysicsComponent>());

		if (!isIntersecting(cpBrick, cpBall)) {
			return;
		}

		mBrick.destroy();

		const float overlapLeft{ cpBall.right() - cpBrick.left() };
		const float overlapRight{ cpBrick.right() - cpBall.left() };
		const float overlapTop{ cpBall.bottom() - cpBrick.top() };
		const float overlapBottom{ cpBrick.bottom() - cpBall.top() };

		const bool ballFromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
		const bool ballFromTop(std::abs(overlapTop) < std::abs(overlapBottom));

		const float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
		const float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

		if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
			cpBall.velocity.x = ballFromLeft ? -Definitions::BallVelocity : Definitions::BallVelocity;
		}
		else {
			cpBall.velocity.y = ballFromTop ? -Definitions::BallVelocity : Definitions::BallVelocity;
		}
	}

	ecs::Entity& GameScene::createBall(void) {
		auto& entity(m_EntityManager.addEntity());

		entity.addComponent<PositionComponent>(sf::Vector2f{ Definitions::WindowWidth / 2.f, Definitions::WindowHeight / 2.f });
		entity.addComponent<PhysicsComponent>(sf::Vector2f{ Definitions::BallRadius, Definitions::BallRadius });
		entity.addComponent<CircleComponent>(Definitions::BallRadius);

		auto& cPhysics(entity.getComponent<PhysicsComponent>());
		cPhysics.velocity = sf::Vector2f{ -Definitions::BallVelocity, -Definitions::BallVelocity };
		cPhysics.onOutOfBounds = [&cPhysics](const sf::Vector2f& mSide) {
			if (mSide.x != 0.f) {
				cPhysics.velocity.x =
					std::abs(cPhysics.velocity.x) * mSide.x;
			}

			if (mSide.y != 0.f) {
				cPhysics.velocity.y =
					std::abs(cPhysics.velocity.y) * mSide.y;
			}
		};

		entity.addGroup(ArkanoidGroup::GBall);

		return entity;
	}

	ecs::Entity& GameScene::createBrick(const sf::Vector2f& _position) {
		const sf::Vector2f halfSize{ Definitions::BlockWidth / 2.f, Definitions::BlockHeight / 2.f };
		auto& entity(m_EntityManager.addEntity());

		entity.addComponent<PositionComponent>(_position);
		entity.addComponent<PhysicsComponent>(halfSize);
		entity.addComponent<RectangleComponent>(halfSize);

		entity.addGroup(ArkanoidGroup::GBrick);

		return entity;		
	}

	ecs::Entity& GameScene::createPaddle(void) {
		const sf::Vector2f halfSize{ Definitions::PaddleWidth / 2.f, Definitions::PaddleHeight / 2.f };
		auto& entity(m_EntityManager.addEntity());

		entity.addComponent<PositionComponent>(sf::Vector2f{ Definitions::WindowWidth / 2.f, Definitions::WindowHeight - 60.f });
		entity.addComponent<PhysicsComponent>(halfSize);
		entity.addComponent<RectangleComponent>(halfSize);
		entity.addComponent<PlayerPaddleControlComponent>();

		entity.addGroup(ArkanoidGroup::GPaddle);

		return entity;
	}
}
