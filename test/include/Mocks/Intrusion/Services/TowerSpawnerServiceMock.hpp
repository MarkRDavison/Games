#ifndef INCLUDED_MOCKS_INTRUSION_SERVICES_TOWER_SPAWNER_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_INTRUSION_SERVICES_TOWER_SPAWNER_SERVICE_MOCK_HPP_

#include <Intrusion/Services/ITowerSpawnerService.hpp>

#include <SFML/Graphics.hpp>

namespace itr {
	
	class TowerSpawnerServiceMock : public ITowerSpawnerService {
	public:
		~TowerSpawnerServiceMock(void) override = default;

		void update(float _delta) override {
			
		}
		bool handleEvent(const sf::Event& _event) override {
			return false;
		}
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override {}

		bool getShowingTowerGhost(void) const override {
			return showingTowerGhost;
		}
		bool getValidLocationForTowerGhost(void) const override {
			return validLocationForTowerGhost;
		}
		sf::Vector2i getGhostCoordinates(void) const override {
			return ghostCoordinates;
		}
		ParsedTower getGhostPrototype(void) const override {
			return ghostPrototype;
		}
		void reset(void) override {
			if (resetCallback) {
				resetCallback();
			}
		}

		bool showingTowerGhost{ false };
		bool validLocationForTowerGhost{ false };
		sf::Vector2i ghostCoordinates;
		ParsedTower ghostPrototype;

		std::function<void(void)> resetCallback;
	};

}

#endif // INCLUDED_MOCKS_INTRUSION_SERVICES_TOWER_SPAWNER_SERVICE_MOCK_HPP_