#ifndef INCLUDED_ASCENDANCE_INFRASTUCTURE_SCENE_HPP_
#define INCLUDED_ASCENDANCE_INFRASTUCTURE_SCENE_HPP_

#include <string>
#include <SFML/Graphics.hpp>

namespace inf {
	class Scene {
	public:
		Scene(const std::string& _name);
		virtual ~Scene();

		const std::string Name;

		virtual void update(float _delta) = 0;
		virtual bool handleEvent(const sf::Event& _event) = 0;
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const = 0;
	};
}

#endif // INCLUDED_ASCENDANCE_INFRASTUCTURE_SCENE_HPP_