#include <Intrusion/Systems/RenderSystem.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/RenderableComponent.hpp>

namespace itr {

	RenderSystem::RenderSystem(void) {
		
	}
	RenderSystem::~RenderSystem(void) {
		
	}

	void RenderSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (const ecs::Entity *_e : _entityManager.getEntitiesByGroup(itr::EntityGroup::GRenderable)) {
			PositionComponent& pc = _e->getComponent<PositionComponent>();
			pc.previousPosition = pc.position;
		}
	}

	void RenderSystem::draw(ecs::EntityManager& _entityManager, sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		for (const ecs::Entity *_e : _entityManager.getEntitiesByGroup(itr::EntityGroup::GRenderable)) {
			_e->getComponentOfBaseType<RenderableComponent>().render(_target, _states, _alpha);
		}
	}

}
