#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_PROTOTYPE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_PROTOTYPE_HPP_

#include <Driller/DataStructures/JobPrototype.hpp>
#include <vector>

namespace drl {

	using WorkerPrototypeId = std::size_t;

	struct WorkerPrototype {

		std::vector<JobPrototypeId> validJobTypes;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_PROTOTYPE_HPP_