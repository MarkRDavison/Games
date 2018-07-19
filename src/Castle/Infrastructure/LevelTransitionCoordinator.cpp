#include <Castle/Infrastructure/LevelTransitionCoordinator.hpp>
#include <EntityComponentSystem/EntityManager.hpp>
#include <Castle/Infrastructure/EntityGroups.hpp>
#include <algorithm>
#include <iostream>

namespace castle {

	LevelTransitionCoordinator::LevelTransitionCoordinator(EntityPrototypeFactory& _entityPrototypeFactory) :
		m_EntityPrototypeFactory(_entityPrototypeFactory),
		m_ActiveLevel(nullptr) {
		
	}

	void LevelTransitionCoordinator::addParsedLevel(const ParsedLevel& _parsedLevel) {
		m_ParsedLevels.emplace_back(_parsedLevel);
	}
	bool LevelTransitionCoordinator::setActiveLevel(const std::string& _levelName) {
		const auto result = std::find_if(m_Levels.begin(), m_Levels.end(), [_levelName](const Level* _level) { return _level->getName() == _levelName; });
		if (result != m_Levels.end()) {
			Level *newLevel = *result;
			if (m_ActiveLevel != nullptr) {
				if (!ecs::EntityManager::swapEntityBetweenManagers(m_ActiveLevel->getEntityManager().getEntitiesByGroup(EntityGroup::GPlayer).front(), m_ActiveLevel->getEntityManager(), newLevel->getEntityManager())) {
					std::cout << "Failed to swap entity to new level " << _levelName << " from level " << m_ActiveLevel->getName() << std::endl;
					return false;
				}
			}
			m_ActiveLevel = newLevel;
			std::cout << "Initialized new level and switched to it: " << _levelName << std::endl;
			m_LevelTransitioned = true;
			return true;
		}

		const auto parsedLevelResult = std::find_if(m_ParsedLevels.begin(), m_ParsedLevels.end(), [_levelName](const ParsedLevel& _parsedLevel) { return _parsedLevel.name == _levelName; });
		if (parsedLevelResult != m_ParsedLevels.end()) {
			Level *l = new Level();
			l->initialize(*parsedLevelResult, m_EntityPrototypeFactory, *this);
			m_Levels.emplace_back(l);
			if (m_ActiveLevel != nullptr) {
				if (!ecs::EntityManager::swapEntityBetweenManagers(m_ActiveLevel->getEntityManager().getEntitiesByGroup(EntityGroup::GPlayer).front(), m_ActiveLevel->getEntityManager(), l->getEntityManager())) {
					std::cout << "Failed to swap entity to new level " << _levelName << " from level " << m_ActiveLevel->getName() << std::endl;
					return false;
				}
			}
			m_ActiveLevel = l;
			std::cout << "Initialized new level and switched to it: " << _levelName << std::endl;
			m_LevelTransitioned = true;
			return true;
		}

		std::cout << "Failed to set active level " << _levelName << ", it wasn't made or initialized" << std::endl;
		return false;
	}
	void LevelTransitionCoordinator::setActiveLevel(Level *_level) {
		m_ActiveLevel = _level;
	}
	Level *LevelTransitionCoordinator::getActiveLevel(void) const {
		return m_ActiveLevel;
	}
	bool LevelTransitionCoordinator::getLevelTransitioned(void) const {
		return m_LevelTransitioned;
	}
	void LevelTransitionCoordinator::resetLevelTransitioned(void) {
		m_LevelTransitioned = false;
	}
}
