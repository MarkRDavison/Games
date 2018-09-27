#ifndef INCLUDED_POLLUTION_SERVICES_WORLD_INTERACTION_SERVICE_HPP_
#define INCLUDED_POLLUTION_SERVICES_WORLD_INTERACTION_SERVICE_HPP_

#include <Pollution/Services/Interfaces/IWorldInteractionService.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/Interfaces/IConfigurationManager.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>

namespace pol {

	class WorldInteractionService : public IWorldInteractionService {
	public:
		WorldInteractionService(inf::InputManager& _inputManager, inf::IConfigurationManager& _config, inf::IResourceService& _resourceService);
		~WorldInteractionService(void) override;

		bool handleEvent(const sf::Event& _event, WorldData& _worldData) override;

		int getWorldSegmentIndexForAngle(const WorldData& _worldData, float _screenRelativeAngle) override;
		int getWorldSegmentForEventCoordinates(const WorldData& _worldData, const sf::Vector2i& _eventCoordinates) override;
		float getAngleRelativeToCenterOfScreen(const sf::Vector2f& _coordinates) const override;
		bool getLengthWithinSnapMargin(const WorldData& _worldData, float _length) const override;
		bool getLengthWithinSnapMargin(const WorldData& _worldData, const sf::Vector2i& _eventCoordinates) const override;
		Definitions::PlaceBuildingResult canPlacePrototypeatSegmentIndex(const WorldData& _worldData, const BuildingData& _prototype, int _segmentIndex) override;

	private:
		inf::InputManager& m_InputManager;
		inf::IConfigurationManager& m_Config;
		inf::IResourceService& m_ResourceService;
	};

}

#endif // INCLUDED_POLLUTION_SERVICES_WORLD_INTERACTION_SERVICE_HPP_