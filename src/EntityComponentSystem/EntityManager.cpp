#include <EntityComponentSystem/EntityManager.hpp>

namespace ecs {

	void EntityManager::update(float _delta) {
		for (auto& e : m_Entities) e->update(_delta);
	}

	void EntityManager::addToGroup(Entity* mEntity, Group mGroup) {
		m_GroupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& EntityManager::getEntitiesByGroup(Group mGroup) {
		return m_GroupedEntities[mGroup];
	}

	void EntityManager::applyActionToAllEntities(const std::function<void(Entity&)>& _function) {
		for (auto& e : m_Entities) {
			_function(*e);
		}
	}

	void EntityManager::refresh() {
		for (unsigned int i = 0; i < m_NewEntities.size(); ++i) {
			m_Entities.emplace_back(std::move(m_NewEntities[i]));
		}
		m_NewEntities.clear();

		for (auto i(0u); i < maxGroups; ++i) {
			auto& v(m_GroupedEntities[i]);

			v.erase(std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
			{
				return !mEntity->isAlive() ||
					!mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		m_Entities.erase(
			std::remove_if(std::begin(m_Entities), std::end(m_Entities),
				[](const std::shared_ptr<Entity>& _entity)
		{
			return !_entity->isAlive();
		}),
			std::end(m_Entities));
	}

	Entity& EntityManager::addEntity() {
		return addEntity("");
	}
	Entity& EntityManager::addEntity(const std::string& _helpfulName) {
		std::shared_ptr<Entity> e = std::make_shared<Entity>(this);

		if (_helpfulName == "") {
			e->name = std::to_string(intptr_t(e.get()));
		}
		else {
			e->name = _helpfulName;
		}

		m_NewEntities.push_back(e);
		return *e;
	}
	Entity& EntityManager::getEntity(const std::string& _helpfulName) {
		const auto result = std::find_if(m_Entities.begin(), m_Entities.end(), [_helpfulName](const std::shared_ptr<Entity>& _entity) { return _entity->name == _helpfulName; });

		if (result != m_Entities.end()) {
			return*(*result);
		}

		throw std::runtime_error("Could not find entity '" + _helpfulName + "'");
	}

	std::weak_ptr<Entity> EntityManager::getWeakEntityRef(Entity* _entity) {
		const auto result = std::find_if(m_Entities.begin(), m_Entities.end(), [_entity](const std::shared_ptr<Entity>& e) { return e.get() == _entity; });

		if (result != m_Entities.end()) {
			return std::weak_ptr<Entity>((*result));
		}

		return std::weak_ptr<Entity>();
	}

	bool EntityManager::swapEntityBetweenManagers(Entity* _entity, EntityManager& _currentManager, EntityManager& _newManager) {
		const auto it = std::find_if(_currentManager.m_Entities.begin(), _currentManager.m_Entities.end(), [_entity](std::shared_ptr<Entity>& e) { return e.get() == _entity; });
		if (it == _currentManager.m_Entities.end()) {
			return false;
		}
		_newManager.m_Entities.push_back(*it);
		_currentManager.m_Entities.erase(it);
		_entity->updateEntityManager(&_newManager);
		return true;
	}

	void EntityManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		for (const auto& e : m_Entities) {
			e->draw(_target, _states);
		}
	}
}
