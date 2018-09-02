#ifndef INCLUDED_KINGDOM_SYSTEMS_RENDER_SYSTEM_HPP_
#define INCLUDED_KINGDOM_SYSTEMS_RENDER_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

namespace kdm {
	
	class RenderSystem : public ecs::System {
	public:
		RenderSystem(void);
		~RenderSystem(void) override;
		void draw(ecs::EntityManager& _entityManager, sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const;
	};

}

#endif // INCLUDED_KINGDOM_SYSTEMS_RENDER_SYSTEM_HPP_