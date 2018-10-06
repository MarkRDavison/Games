#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_JOB_PROTOTYPE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_JOB_PROTOTYPE_HPP_

#include <SFML/System/Vector2.hpp>
#include <cstdlib>

namespace drl {

	using JobPrototypeId = std::size_t;

	struct JobPrototype {
		float workRequired{ 0.0f };
		bool repeats{ false };
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_JOB_PROTOTYPE_HPP_