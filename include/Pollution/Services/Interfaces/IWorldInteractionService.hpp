#ifndef INCLUDED_POLLUTION_SERVICES_INTERFACES_I_WORLD_INTERACTION_SERVICE_HPP_
#define INCLUDED_POLLUTION_SERVICES_INTERFACES_I_WORLD_INTERACTION_SERVICE_HPP_

#include <SFML/Window/Event.hpp>
#include <Pollution/DataStructures/WorldData.hpp>
#include <Pollution/Infrastructure/Definitions.hpp>

namespace pol {

	class IWorldInteractionService {
	public:
		virtual ~IWorldInteractionService(void) = 0 {}

		virtual bool handleEvent(const sf::Event& _event, WorldData& _worldData) = 0;

		virtual int getWorldSegmentIndexForAngle(const WorldData& _worldData, float _screenRelativeAngle) = 0;
		virtual int getWorldSegmentForEventCoordinates(const WorldData& _worldData, const sf::Vector2i& _eventCoordinates) = 0;
		virtual float getAngleRelativeToCenterOfScreen(const sf::Vector2f& _coordinates) const = 0;
		virtual bool getLengthWithinSnapMargin(const WorldData& _worldData, float _length) const = 0;
		virtual bool getLengthWithinSnapMargin(const WorldData& _worldData, const sf::Vector2i& _eventCoordinates) const = 0;
		virtual Definitions::PlaceBuildingResult canPlacePrototypeatSegmentIndex(const WorldData& _worldData, const BuildingData& _prototype, int _segmentIndex) = 0;
	};

}

#endif // INCLUDED_POLLUTION_SERVICES_INTERFACES_I_WORLD_INTERACTION_SERVICE_HPP_