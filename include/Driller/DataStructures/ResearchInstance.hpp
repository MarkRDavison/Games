#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_INSTANCE_HPP_

#include <Infrastructure/DataStructures/ResourceBundle.hpp>
#include <functional>

namespace drl {

	struct ResearchInstance {
		inf::ResourceBundle cost;
		unsigned level{0u};
		std::function<void(std::size_t, unsigned)> callback;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_RESEARCH_INSTANCE_HPP_