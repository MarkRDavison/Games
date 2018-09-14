#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_RESOURCE_BUNDLE_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_RESOURCE_BUNDLE_HPP_

#include <vector>
#include <string>

namespace itr {

	
	struct ResourceBundle {
		struct Resource {
			std::string name;
			int amount{0};
		};

		std::vector<Resource> resources;
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_RESOURCE_BUNDLE_HPP_