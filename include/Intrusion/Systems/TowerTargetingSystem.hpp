#ifndef INCLUDED_INTRUSION_SYSTEMS_TOWER_TARGETING_SYSTEM_HPP_
#define INCLUDED_INTRUSION_SYSTEMS_TOWER_TARGETING_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>
#include <Intrusion/Components/PositionComponent.hpp>
#include <Intrusion/Components/TowerTargetingComponent.hpp>

namespace itr {
	
	/**
	 * \brief TODO: Should we subscribe to something that notifies when enemeies die?
	 * Then we can remove targets etc etc
	 */
	class TowerTargetingSystem : public ecs::System {
	public:
		TowerTargetingSystem(void);
		~TowerTargetingSystem(void) override;

		void update(float _delta, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager);

		static bool targetStillInRange(const PositionComponent& _towerPositionComponent, const TowerTargetingComponent& _towerTargetingComponent);
	};

}

#endif // INCLUDED_INTRUSION_SYSTEMS_TOWER_TARGETING_SYSTEM_HPP_