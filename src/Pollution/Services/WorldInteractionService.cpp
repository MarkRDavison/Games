#include <Pollution/Services/WorldInteractionService.hpp>
#include <Utility/VectorMath.hpp>

namespace pol {

	WorldInteractionService::WorldInteractionService(inf::InputManager& _inputManager, inf::IConfigurationManager& _config, inf::IResourceService& _resourceService) :
		m_InputManager(_inputManager),
		m_Config(_config),
		m_ResourceService(_resourceService) {
		
	}

	WorldInteractionService::~WorldInteractionService(void) {
	
	}

	bool WorldInteractionService::handleEvent(const sf::Event& _event, WorldData& _worldData) {
		return false;
	}

	int WorldInteractionService::getWorldSegmentIndexForAngle(const WorldData& _worldData, float _screenRelativeAngle) {
		const float SideAngleSize = 360.0f / static_cast<float>(_worldData.Sides);

		return (_worldData.Sides + static_cast<int>(std::floorf((_screenRelativeAngle - _worldData.rotation) / SideAngleSize))) % _worldData.Sides;
	}

	int WorldInteractionService::getWorldSegmentForEventCoordinates(const WorldData& _worldData, const sf::Vector2i& _eventCoordinates) {
		const float Scale = m_Config.getGameViewScale();
		const sf::Vector2f& mousePosition = sf::Vector2f(m_InputManager.getMousePositionRelativeToCenter(_eventCoordinates)) / Scale;
		const float angle = getAngleRelativeToCenterOfScreen(mousePosition);
		return getWorldSegmentIndexForAngle(_worldData, angle);
	}

	float WorldInteractionService::getAngleRelativeToCenterOfScreen(const sf::Vector2f& _coordinates) const {
		const sf::Vector2f dir = inf::VectorMath::normalise(_coordinates);
		float angle = inf::VectorMath::toAngle(dir, inf::VectorMath::AngleType::Degrees);
		if (angle < 0.0f) {
			angle += 360.0f;
		}
		else if (angle >= 360.0f) {
			angle -= 360.0f;
		}

		return angle;
	}

	bool WorldInteractionService::getLengthWithinSnapMargin(const WorldData& _worldData, float _length) const {
		return 1.0f - _worldData.SnapMargin <= _length && _length <= 1.0f + _worldData.SnapMargin;
	}

	bool WorldInteractionService::getLengthWithinSnapMargin(const WorldData& _worldData, const sf::Vector2i& _eventCoordinates) const {
		const sf::Vector2f& mousePosition = sf::Vector2f(m_InputManager.getMousePositionRelativeToCenter()) / m_Config.getGameViewScale();
		const float length = inf::VectorMath::length(mousePosition);
		return getLengthWithinSnapMargin(_worldData, length);
	}

	Definitions::PlaceBuildingResult WorldInteractionService::canPlacePrototypeatSegmentIndex(const WorldData& _worldData, const BuildingData& _prototype, int _segmentIndex) {
		if (!m_ResourceService.canAfford(_prototype.cost)) {
			return Definitions::PlaceBuildingResult::InsufficientResources;
		}

		const BuildingData& currentBuilding = _worldData.buildings[static_cast<unsigned>(_segmentIndex)];
		if (currentBuilding.active && currentBuilding.age >= _prototype.age) {
			return Definitions::PlaceBuildingResult::CannotOverwrite;
		}

		return Definitions::PlaceBuildingResult::CanPlace;
	}

}
