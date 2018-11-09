#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_CATEGORY_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_CATEGORY_HPP_

#include <Driller/DataStructures/ResearchInstance.hpp>
#include <vector>

namespace drl {

	using ResearchId = std::size_t;
	
	struct ResearchCategory {
		ResearchId categoryId;
		std::vector<ResearchInstance> instances;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_CATEGORY_HPP_