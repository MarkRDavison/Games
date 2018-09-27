#ifndef INCLUDED_POLLUTION_GAME_OBJECTS_BUILDING_OBJECT_HPP_
#define INCLUDED_POLLUTION_GAME_OBJECTS_BUILDING_OBJECT_HPP_

#include <SFML/Graphics.hpp>

#include <Pollution/DataStructures/BuildingData.hpp>
#include <Pollution/DataStructures/AnimationData.hpp>

namespace pol {
	
	class BuildingObject {
	public:
		BuildingObject(BuildingData *_buildingData, Animation *_animation, const sf::Texture& _texture);
		~BuildingObject(void);

		void update(float _delta);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const;

		void reset(BuildingData *_buildingData, Animation *_animation);

		BuildingData& getBuildingData(void);
		const BuildingData& getBuildingData(void) const;

	protected:
		void updateAnimation(unsigned _index);

	private:
		BuildingData *m_BuildingData;
		Animation *m_Animation;
		sf::Sprite m_Sprite;
		unsigned m_CurrentFrameIndex{ 0 };
	};

}

#endif // INCLUDED_POLLUTION_GAME_OBJECTS_BUILDING_OBJECT_HPP_