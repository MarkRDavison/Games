#ifndef INCLUDED_INTRUSION_SYSTEMS_RENDER_SYSTEM_HPP_
#define INCLUDED_INTRUSION_SYSTEMS_RENDER_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

namespace itr {

	class RenderSystem : public ecs::System {
	public:
		RenderSystem(void);
		~RenderSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		void draw(ecs::EntityManager& _entityManager, sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const;
	};

}

#endif // INCLUDED_INTRUSION_SYSTEMS_RENDER_SYSTEM_HPP_