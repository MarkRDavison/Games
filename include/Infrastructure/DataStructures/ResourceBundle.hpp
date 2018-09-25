#ifndef INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_RESOURCE_BUNDLE_HPP_
#define INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_RESOURCE_BUNDLE_HPP_

#include <string>
#include <vector>

namespace inf {

	struct ResourceBundle {
		struct Resource {
			std::string name;
			int amount{ 0 };
		};

		std::vector<Resource> resources;
	};

}

#endif // INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_RESOURCE_BUNDLE_HPP_