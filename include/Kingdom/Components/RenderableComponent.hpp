#ifndef INCLUDED_KINGDOM_COMPONENTS_RENDERABLE_COMPONENT_HPP_
#define INCLUDED_KINGDOM_COMPONENTS_RENDERABLE_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <Kingdom/Components/PositionComponent.hpp>

namespace kdm {
	
	struct RenderableComponent : ecs::Component {
		PositionComponent *position{ nullptr };

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
		}

		virtual void render(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const = 0;
	};

}

#endif // INCLUDED_KINGDOM_COMPONENTS_RENDERABLE_COMPONENT_HPP_