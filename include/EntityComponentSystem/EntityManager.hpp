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

		Entity& addEntity();
		Entity& addEntity(const std::string& _helpfulName);

		static bool swapEntityBetweenManagers(Entity *_entity, EntityManager& _currentManager, EntityManager& _newManager);

		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

	private:
		std::vector<std::unique_ptr<Entity>> m_Entities;
		std::vector<std::unique_ptr<Entity>> m_NewEntities;
		std::array<std::vector<Entity*>, maxGroups> m_GroupedEntities;
	};
}

#endif // INCLUDED_ENTITY_COMPONENT_SYSTEM_ENTITY_MANAGER_HPP_