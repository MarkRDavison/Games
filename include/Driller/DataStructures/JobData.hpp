#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_JOB_DATA_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_JOB_DATA_HPP_

#include <Driller/DataStructures/JobInstance.hpp>
#include <vector>

namespace drl {
	
	struct JobData {
		std::vector<JobInstance> jobs;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_JOB_DATA_HPP_