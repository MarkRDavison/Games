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

		std::string getResources(void) {
			std::string str;

			for (const Resource& resource : resources) {
				str += resource.name + ": " + std::to_string(resource.amount) + "\n";
			}

			return str;
		}
	};

}

#endif // INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_RESOURCE_BUNDLE_HPP_