#ifndef INCLUDED_POLLUTION_DATA_STRUCTURES_WORLD_DATA_HPP_
#define INCLUDED_POLLUTION_DATA_STRUCTURES_WORLD_DATA_HPP_

#include <vector>
#include <Pollution/DataStructures/BuildingData.hpp>

namespace pol {

	struct WorldDataInitialisationPackage {
		int Sides{ 0 };
		float SnapMargin{ 0.0f };

		float rotation{ 0.0f };
		float rotationRate{ 0.0f };
	};
	
	struct WorldData {
		int Sides{ 0 };
		float SnapMargin{ 0.0f };

		float rotation{ 0.0f };
		float rotationRate{ 0.0f };

		std::vector<BuildingData> buildings;
	};

}

#endif // INCLUDED_POLLUTION_DATA_STRUCTURES_WORLD_DATA_HPP_