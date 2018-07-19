#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/EntityManager.hpp>

namespace ecs {
	void Entity::addGroup(Group mGroup) noexcept 	{
		m_GroupBitset[mGroup] = true;
		m_EntityManager->addToGroup(this, mGroup);
	}
	void Entity::delGroup(Group mGroup) noexcept {
		m_GroupBitset[mGroup] = false;
	}
	void Entity::updateEntityManager(EntityManager *_entityManager) noexcept {
		m_EntityManager = _entityManager;
		for (std::size_t g = 0; g < maxGroups; g++) {
			if (m_GroupBitset[g]) {
				m_EntityManager->addToGroup(this, g);
			}
		}
	}
}