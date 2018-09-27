#include <Pollution/GameObjects/WorldObject.hpp>

namespace pol {

	WorldObject::WorldObject(WorldData& _worldData) :
		m_WorldData(_worldData) {
		
	}
	WorldObject::~WorldObject(void) {
		
	}

	void WorldObject::update(float _delta) {
		
	}
	bool WorldObject::handleEvent(const sf::Event& _event) {
		return false;
	}
	void WorldObject::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		_target.draw(m_PlanetSprite, _states);
	}

	WorldData& WorldObject::getWorldData(void) {
		return m_WorldData;
	}
	const WorldData& WorldObject::getWorldData(void) const {
		return m_WorldData;
	}

	void WorldObject::setWorldTexture(const sf::Texture& _texture) {
		m_PlanetSprite.setTexture(_texture);
		m_PlanetSprite.setOrigin(sf::Vector2f(_texture.getSize()) / 2.0f);
	}

}
