#ifndef INCLUDED_POLLUTION_GAME_OBJECTS_WORLD_OBJECT_HPP_
#define INCLUDED_POLLUTION_GAME_OBJECTS_WORLD_OBJECT_HPP_

#include <Pollution/DataStructures/WorldData.hpp>

#include <SFML/Graphics.hpp>

namespace pol {
	
	class WorldObject {
	public:
		WorldObject(WorldData& _worldData);
		~WorldObject(void);

		void update(float _delta);
		bool handleEvent(const sf::Event& _event);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const;

		WorldData& getWorldData(void);
		const WorldData& getWorldData(void) const;

		void setWorldTexture(const sf::Texture& _texture);

	private:
		WorldData& m_WorldData;
		sf::Sprite m_PlanetSprite;
	};

}

#endif // INCLUDED_POLLUTION_GAME_OBJECTS_WORLD_OBJECT_HPP_