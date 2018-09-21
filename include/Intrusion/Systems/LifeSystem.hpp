#ifndef INCLUDED_INTRUSION_SYSTEMS_LIFE_SYSTEM_HPP_
#define INCLUDED_INTRUSION_SYSTEMS_LIFE_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>
#include <Intrusion/Services/ILevelResourceService.hpp>

namespace itr {
	
	class LifeSystem : public ecs::System {
	public:
		LifeSystem(ILevelResourceService& _levelResourceService);
		~LifeSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		void updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager) const;

	private:
		ILevelResourceService& m_LevelResourceService;
	};

}

#endif // INCLUDED_INTRUSION_SYSTEMS_LIFE_SYSTEM_HPP_