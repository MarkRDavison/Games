#include <Pollution/GameObjects/BuildingObject.hpp>

namespace pol {
	
	BuildingObject::BuildingObject(BuildingData *_buildingData, Animation *_animation, const sf::Texture& _texture) :
		m_BuildingData(_buildingData),
		m_Animation(_animation),
		m_Sprite(_texture) {
		
		updateAnimation(0);
	}
	BuildingObject::~BuildingObject(void) {
		
	}

	void BuildingObject::update(float _delta) {
		if (m_Animation->frames.empty()) {
			return;
		}
		if (m_BuildingData->accumulatedAnimationTime >= m_Animation->frames[m_CurrentFrameIndex].duration) {
			m_BuildingData->accumulatedAnimationTime -= m_Animation->frames[m_CurrentFrameIndex].duration;
			updateAnimation(m_CurrentFrameIndex + 1);
		}
	}
	void BuildingObject::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		_target.draw(m_Sprite, _states);
	}

	void BuildingObject::reset(BuildingData* _buildingData, Animation* _animation) {
		m_BuildingData = _buildingData;
		m_Animation = _animation;

		updateAnimation(0);
	}

	BuildingData& BuildingObject::getBuildingData(void) {
		return *m_BuildingData;
	}
	const BuildingData& BuildingObject::getBuildingData(void) const {
		return *m_BuildingData;
	}

	void BuildingObject::updateAnimation(unsigned _index) {
		if (m_Animation->frames.empty()) {
			return;
		}
		if (_index >= m_Animation->frames.size()) {
			_index = 0;
		}
		m_CurrentFrameIndex = _index;

		m_Sprite.setTextureRect(m_Animation->frames[m_CurrentFrameIndex].bounds);
		m_Sprite.setOrigin(32.0f, 56.0f);
	}

}
