#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/EntityManager.hpp>

namespace ecs {
	void Entity::addGroup(Group mGroup) noexcept 	{
		m_GroupBitset[mGroup] = true;
		m_EntityManager.addToGroup(this, mGroup);
	}void Entity::delGroup(Group mGroup) noexcept {
		m_GroupBitset[mGroup] = false;
	}
}