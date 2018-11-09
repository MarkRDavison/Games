#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_DATA_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_DATA_HPP_

#include <Driller/DataStructures/ResearchCategory.hpp>
#include <vector>

namespace drl {
	
	struct ResearchData {
		std::vector<ResearchCategory> categories;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_DATA_HPP_