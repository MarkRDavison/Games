#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_JOB_COMPLETE_DELEGATE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_JOB_COMPLETE_DELEGATE_HPP_

#include <Driller/DataStructures/JobInstance.hpp>
#include <functional> 

namespace drl {
	
	using JobCompleteDelegate = std::function<void(const JobInstance&)>;

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_JOB_COMPLETE_DELEGATE_HPP_