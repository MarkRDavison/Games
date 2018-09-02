#include <Kingdom/Systems/RenderSystem.hpp>
#include <Kingdom/Infrastructure/KingdomEntityGroups.hpp>
#include <Kingdom/Components/RenderableComponent.hpp>

namespace kdm {
	
	RenderSystem::RenderSystem(void) {
		
	}
	RenderSystem::~RenderSystem(void) {
		
	}
	void RenderSystem::draw(ecs::EntityManager& _entityManager, sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		for (const auto& _e : _entityManager.getEntitiesByGroup(kdm::EntityGroup::GRenderable)) {
			_e->getComponentOfBaseType<RenderableComponent>().render(_target, _states, _alpha);
		}
	}

}
