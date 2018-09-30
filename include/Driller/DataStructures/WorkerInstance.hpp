#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_INSTANCE_HPP_

#include <Driller/Infrastructure/Definitions.hpp>
#include <Driller/DataStructures/JobPrototype.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <Infrastructure/DataStructures/Path.hpp>

namespace drl {

	struct WorkerInstance {

		enum class WorkerState {
			Idle,
			MovingToJob,
			WorkingJob
		};

		EntityId Id;

		sf::Vector2f position;

		bool hasAllocatedJob{ false };
		EntityId allocatedJobId{ 0u };

		std::vector<JobPrototypeId> validJobTypes;

		WorkerState state{ WorkerState::Idle };

		struct WorkerPathfindingInstance {
			inf::Path path;
		} path;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_INSTANCE_HPP_