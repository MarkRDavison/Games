#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_INSTANCE_HPP_

#include <Driller/Infrastructure/Definitions.hpp>
#include <Driller/DataStructures/JobPrototype.hpp>
#include <Driller/DataStructures/NeedInstance.hpp>
#include <Driller/DataStructures/WorkerPrototype.hpp>
#include <Infrastructure/DataStructures/Path.hpp>
#include <vector>

namespace drl {

	struct WorkerInstance {

		enum class WorkerState {
			Idle,
			MovingToJob,
			WorkingJob,
			MovingToNeed,
			RestoringNeed
		};

		EntityId Id;

		sf::Vector2f position;

		bool hasAllocatedJob{ false };
		bool removalRequired{ false };
		EntityId allocatedJobId{ 0u };

		std::vector<JobPrototypeId> validJobTypes;

		WorkerState state{ WorkerState::Idle };
		WorkerPrototypeId prototypeId;

		struct WorkerPathfindingInstance {
			inf::Path path;
		} path;

		NeedInstance needs;
		EntityId restoringNeedProviderId{ 0u };
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_INSTANCE_HPP_