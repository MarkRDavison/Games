#ifndef INCLUDED_INTRUSION_COMPONENTS_RENDERABLE_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_RENDERABLE_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <Intrusion/Components/PositionComponent.hpp>

namespace itr {
	
	struct RenderableComponent : ecs::Component {
		sf::Color overlayColor{ sf::Color::White };
		PositionComponent *position{ nullptr };

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
		}

		virtual void render(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const = 0;
	};

}

#endif // #define INCLUDED_INTRUSION_COMPONENTS_RENDERABLE_COMPONENT_HPP_
