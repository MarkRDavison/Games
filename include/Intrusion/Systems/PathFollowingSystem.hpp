#ifndef INCLUDED_INTRUSION_SYSTEMS_PATH_FOLLOWING_SYSTEM_HPP_
#define INCLUDED_INTRUSION_SYSTEMS_PATH_FOLLOWING_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

#include <Intrusion/Services/ILevelResourceService.hpp>

namespace itr {

	class PathFollowingSystem : public ecs::System {
	public:
		explicit PathFollowingSystem(ILevelResourceService& _levelResourceService);

		void update(float _delta, ecs::EntityManager& _entityManager) override;
		void updateEntity(float _delta, ecs::Entity* _entity, ecs::EntityManager& _entityManager) const;

	protected:
		ILevelResourceService& m_LevelResourceService;
	};
}

#endif // INCLUDED_INTRUSION_SYSTEMS_PATH_FOLLOWING_SYSTEM_HPP_