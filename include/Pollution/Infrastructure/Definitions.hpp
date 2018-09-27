#ifndef INCLUDED_POLLUTION_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_POLLUTION_INFRASTRUCTURE_DEFINITIONS_HPP_

namespace pol {
	
	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr const char GameLuaScope[] = "GameLuaScope";

		static constexpr const char GoldResourceName[] = "Gold";
		static constexpr const char SpecialResourceName[] = "Special";
		static constexpr const char YearResourceName[] = "Year";
		static constexpr const char AgeResourceName[] = "Age";

		static constexpr const char TestSunTextureName[] = "test_sun";
		static constexpr const char BuildingTextureName[] = "building_sprite_sheet";

		static constexpr const float YearAccumulationRate{ 1.2f };
		
		static constexpr const unsigned NumberBuildings{ 10 };

		enum class PlaceBuildingResult {
			CanPlace,
			InsufficientResources,
			CannotOverwrite
		};
	};

}

#endif // INCLUDED_POLLUTION_INFRASTRUCTURE_DEFINITIONS_HPP_