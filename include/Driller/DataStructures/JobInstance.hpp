#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_JOB_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_JOB_INSTANCE_HPP_

#include <Driller/Infrastructure/Definitions.hpp>
#include <Driller/DataStructures/JobPrototype.hpp>
#include <SFML/System/Vector2.hpp>

namespace drl {

	struct JobInstance {
		EntityId Id;

		sf::Vector2i coordinates;
		sf::Vector2i bounds;
		sf::Vector2f jobPerformOffset;

		bool allocated{ false };
		EntityId allocatedWorkerId{ 0u };

		JobPrototypeId prototypeId;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_JOB_INSTANCE_HPP_