#include <Hurricane/Systems/PlayerControlSystem.hpp>
#include <Hurricane/Components/PlayerComponent.hpp>
#include <Hurricane/Components/PositionComponent.hpp>
#include <Hurricane/Components/SpriteComponent.hpp>
#include <Hurricane/Components/CollisionComponent.hpp>
#include <Hurricane/Components/MovementComponent.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>

#include <EntityComponentSystem/Entity.hpp>

#include <Utility/VectorMath.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace hur {

	PlayerControlSystem::PlayerControlSystem(inf::InputManager& _inputManager, inf::TextureManager& _textureManager) :
		m_InputManager(_inputManager),
		m_TextureManager(_textureManager) {
		
	}

	void PlayerControlSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(hurr::EntityGroup::GPlayer)) {
			updateEntity(e, _entityManager);
		}
	}
	bool PlayerControlSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void PlayerControlSystem::updateEntity(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const {
		PlayerComponent& pc = _entity->getComponent<PlayerComponent>();
		MovementComponent& mc = _entity->getComponent<MovementComponent>();

		pc.direction = {};

		if (m_InputManager.isKeyPressed(sf::Keyboard::A)) {
			pc.direction.x -= 1.0f;
		}
		if (m_InputManager.isKeyPressed(sf::Keyboard::D)) {
			pc.direction.x += 1.0f;
		}
		if (m_InputManager.isKeyPressed(sf::Keyboard::W)) {
			pc.direction.y -= 1.0f;
		}
		if (m_InputManager.isKeyPressed(sf::Keyboard::S)) {
			pc.direction.y += 1.0f;
		}

		if (pc.direction != sf::Vector2f()) {
			inf::VectorMath::normalise(pc.direction);			
		}
		mc.velocity = pc.direction * pc.speed;

		if (pc.canFire) {
			if (m_InputManager.isKeyPressed(sf::Keyboard::Space)) {
				pc.canFire = false;
				createLaser(_entity, _entityManager);
			}
		} else {
			if (!m_InputManager.isKeyPressed(sf::Keyboard::Space)) {
				pc.canFire = true;
			}
		}
	}

	void PlayerControlSystem::createLaser(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const {
		ecs::Entity& e = _entityManager.addEntity();
		e.addGroup(hurr::EntityGroup::GProjectile);
		e.addGroup(hurr::EntityGroup::GKinematic);
		e.addGroup(hurr::EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(_entity->getComponent<PositionComponent>().position - sf::Vector2f(0.0f, _entity->getComponent<CollisionComponent>().size.y));
		e.addComponent<MovementComponent>().velocity.y = -16.0f;
		const sf::Vector2f size{ 9.0f, 54.0f };
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("laser_blue"), sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		e.addComponent<CollisionComponent>(sf::Vector2f(size.x / 64.0f, size.y / 64.0f));
	}
}
