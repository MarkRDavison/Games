#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_DATA_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_DATA_HPP_

#include <Driller/DataStructures/WorkerInstance.hpp>
#include <vector>

namespace drl {

	struct WorkerData {
		std::vector<WorkerInstance> workers;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_WORKER_DATA_HPP_