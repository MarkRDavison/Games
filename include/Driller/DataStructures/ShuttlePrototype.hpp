#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_PROTOTYPE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_PROTOTYPE_HPP_

#include <cstdlib>

namespace drl {

	using ShuttlePrototypeId = std::size_t;

	struct ShuttlePrototype {
		int capacity{1u};
		float loadingTime{ 5.0f };
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_PROTOTYPE_HPP_