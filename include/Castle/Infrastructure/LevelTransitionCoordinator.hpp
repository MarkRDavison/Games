#ifndef INCLUDED_CASTLE_INFRASTRUCTURE_LEVEL_TRANSITION_COORDINATOR_HPP_
#define INCLUDED_CASTLE_INFRASTRUCTURE_LEVEL_TRANSITION_COORDINATOR_HPP_

#include <Castle/DataStructures/ParsedLevel.hpp>
#include <Castle/GameObjects/Level.hpp>
#include <Castle/Infrastructure/EntityPrototypeFactory.hpp>
#include <vector>
#include <string>

namespace castle {
	class LevelTransitionCoordinator {
	public:
		LevelTransitionCoordinator(EntityPrototypeFactory& _entityPrototypeFactory);

		void addParsedLevel(const ParsedLevel& _parsedLevel);
		bool setActiveLevel(const std::string& _levelName);
		void setActiveLevel(Level *_level);
		Level *getActiveLevel(void) const;
		bool getLevelTransitioned(void) const;
		void resetLevelTransitioned(void);

	private:
		bool m_LevelTransitioned{ false };
		EntityPrototypeFactory& m_EntityPrototypeFactory;
		Level *m_ActiveLevel;
		std::vector<Level *> m_Levels;
		std::vector<ParsedLevel> m_ParsedLevels;
	};
}

#endif // INCLUDED_CASTLE_INFRASTRUCTURE_LEVEL_TRANSITION_COORDINATOR_HPP_