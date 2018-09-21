#ifndef INCLUDED_INTRUSION_SERVICES_I_TOWER_SPAWNER_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_I_TOWER_SPAWNER_SERVICE_HPP_

#include <functional>

#include <Intrusion/DataStructures/ParsedTower.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace itr {
	
	class ITowerSpawnerService {
	public:
		virtual ~ITowerSpawnerService(void) = default;
		
		virtual void update(float _delta) = 0;
		virtual bool handleEvent(const sf::Event& _event) = 0;
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const = 0;

		virtual bool beginGhostForPrototype(const ParsedTower& _prototype) = 0; 
		virtual bool attemptPlacingGhost(const sf::Vector2i& _eventCoordinates) = 0;
		virtual bool getShowingTowerGhost(void) const = 0;
		virtual bool getValidLocationForTowerGhost(void) const = 0;
		virtual sf::Vector2i getGhostCoordinates(void) const = 0;
		virtual ParsedTower getGhostPrototype(void) const = 0;
		virtual void reset(void) = 0;

		std::function<void(const ParsedTower&, const sf::Vector2i&)> prototypeSpawned;
	};

}

#endif // INCLUDED_INTRUSION_SERVICES_I_TOWER_SPAWNER_SERVICE_HPP_