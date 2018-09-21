#ifndef INCLUDED_ENTITY_COMPONENT_SYSTEM_ENTITY_MANAGER_HPP_
#define INCLUDED_ENTITY_COMPONENT_SYSTEM_ENTITY_MANAGER_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <functional>

namespace ecs {
	class EntityManager {
	public:
		void update(float _delta);

		void addToGroup(Entity* mEntity, Group mGroup);

		std::vector<Entity*>& getEntitiesByGroup(Group mGroup);
		void applyActionToAllEntities(const std::function<void(Entity&)>& _function);

		void refresh();
		std::size_t getNumberOfEntities(void) const noexcept {
			return m_Entities.size();
		}

		Entity& addEntity();
		Entity& addEntity(const std::string& _helpfulName);
		Entity& getEntity(const std::string& _helpfulName);
		std::weak_ptr<Entity> getWeakEntityRef(Entity *_entity);

		static bool swapEntityBetweenManagers(Entity *_entity, EntityManager& _currentManager, EntityManager& _newManager);

		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

	private:
		std::vector<std::shared_ptr<Entity>> m_Entities;
		std::vector<std::shared_ptr<Entity>> m_NewEntities;
		std::array<std::vector<Entity*>, maxGroups> m_GroupedEntities;
	};
}

#endif // INCLUDED_ENTITY_COMPONENT_SYSTEM_ENTITY_MANAGER_HPP_