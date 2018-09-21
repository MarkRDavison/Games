#ifndef INCLUDED_INTRUSION_SERVICES_TOWER_SPAWNER_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_TOWER_SPAWNER_SERVICE_HPP_

#include <Infrastructure/InputManager.hpp>

#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>

#include <Intrusion/Services/ILevelResourceService.hpp>
#include <Intrusion/Services/ITowerSpawnerService.hpp>
#include <Intrusion/Services/ITowerPlaceableSurfaceService.hpp>

namespace itr {

	class TowerSpawnerService : public ITowerSpawnerService {
	public:
		TowerSpawnerService(inf::InputManager& _inputManager, IntrusionConfigurationManager& _config, ILevelResourceService& _levelResourceService, ITowerPlaceableSurfaceService& _towerPlaceableSurfaceService);
		~TowerSpawnerService(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

		bool beginGhostForPrototype(const ParsedTower& _prototype) override;
		bool attemptPlacingGhost(const sf::Vector2i& _eventCoordinates) override;
		bool getShowingTowerGhost(void) const override;
		bool getValidLocationForTowerGhost(void) const override;
		sf::Vector2i getGhostCoordinates(void) const override;
		ParsedTower getGhostPrototype(void) const override;
		void reset(void) override;

	protected:
		void updateGhostLocationValid(const ITowerPlaceableSurface* surface);
		void updateGhostPosition(const sf::Vector2i& _eventCoordinates);

	private:
		inf::InputManager& m_InputManager;
		IntrusionConfigurationManager& m_Config;
		ILevelResourceService& m_LevelResourceService;
		ITowerPlaceableSurfaceService& m_TowerPlaceableSurfaceService;

		bool m_ShowingTowerGhost{ false };
		bool m_ValidLocationForTowerGhost{ false };
		sf::Vector2i m_GhostTowerTileCoords;
		ParsedTower m_CurrentPrototype;
	};

}

#endif // INCLUDED_INTRUSION_SERVICES_TOWER_SPAWNER_SERVICE_HPP_