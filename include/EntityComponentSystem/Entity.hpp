#ifndef INCLUDED_ENTITY_COMPONENT_SYSTEM_ENTITY_HPP_
#define INCLUDED_ENTITY_COMPONENT_SYSTEM_ENTITY_HPP_

#include <EntityComponentSystem/ECS.hpp>
#include <EntityComponentSystem/Component.hpp>
#include <vector>
#include <cassert>
#include <typeinfo>

namespace ecs {
	class EntityManager;
	class Entity {
	public:
		Entity(EntityManager *_entityManager) :
			m_EntityManager(_entityManager) {
			
		}
		
		void update(float _delta) 		{
			for (auto& c : m_Components) {
				c->update(_delta);
			}
		}
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
			for (const auto& c : m_Components) {
				c->draw(_target, _states);
			}
		}

		bool isAlive() const {
			return m_Alive;
		}
		void destroy() {
			m_Alive = false;
		}

		template <typename T>
		bool hasComponent() const 		{
			return m_ComponentBitset[getComponentTypeID<T>()];
		}

		bool hasGroup(Group mGroup) const noexcept {
			return m_GroupBitset[mGroup];
		}


		void addGroup(Group mGroup) noexcept;
		void delGroup(Group mGroup) noexcept;
		void updateEntityManager(EntityManager *_entityManager) noexcept;

		template <typename T, typename... TArgs>
		T& addComponent(TArgs&&... mArgs) {
			assert(!hasComponent<T>());

			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			m_Components.emplace_back(std::move(uPtr));

			m_ComponentArray[getComponentTypeID<T>()] = c;
			m_ComponentBitset[getComponentTypeID<T>()] = true;

			c->init();
			return *c;
		}

		std::string name;

		template <typename T>
		T& getComponent() const {
			assert(hasComponent<T>());
			auto ptr(m_ComponentArray[getComponentTypeID<T>()]);
			return *reinterpret_cast<T*>(ptr);
		}

		template <typename T>
		T& getComponentOfBaseType() const {
			for (const std::unique_ptr<Component>& c : m_Components) {
				T *btc = dynamic_cast<T*>(c.get());
				if (btc != nullptr) {
					return *reinterpret_cast<T*>(btc);
				}
			}
			throw std::runtime_error("Cannot find component inheriting " + std::string(typeid(T).name()));
		}

	private:
		EntityManager *m_EntityManager;
		bool m_Alive{ true };

		GroupBitset m_GroupBitset;
		ComponentArray m_ComponentArray;
		ComponentBitset m_ComponentBitset;
		std::vector<std::unique_ptr<Component>> m_Components;

	};
}

#endif // INCLUDED_ENTITY_COMPONENT_SYSTEM_ENTITY_HPP_