#include <Intrusion/Services/TowerSpawnerService.hpp>

#include <SFML/Graphics.hpp>

namespace itr {

	TowerSpawnerService::TowerSpawnerService(inf::InputManager& _inputManager, IntrusionConfigurationManager& _config, ITowerPlaceableSurfaceService& _towerPlaceableSurfaceService) :
		m_InputManager(_inputManager),
		m_Config(_config),
		m_TowerPlaceableSurfaceService(_towerPlaceableSurfaceService) {
		
	}
	TowerSpawnerService::~TowerSpawnerService(void) {
		
	}

	void TowerSpawnerService::update(float _delta) {
		
	}
	bool TowerSpawnerService::handleEvent(const sf::Event& _event) {
		if (_event.key.code == sf::Keyboard::Escape) {
			if (m_ShowingTowerGhost) {
				reset();
				return true;
			}
		}
		if (_event.type == sf::Event::MouseMoved) {
			if (m_ShowingTowerGhost) {
				updateGhostPosition({ _event.mouseMove.x, _event.mouseMove.y });
			}
		}
		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.mouseButton.button == sf::Mouse::Left) {
				if (attemptPlacingGhost({ _event.mouseButton.x, _event.mouseButton.y })) {
					reset();
					return true;
				}
			}
		}
		return false;
	}
	void TowerSpawnerService::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		if (!m_ShowingTowerGhost || m_GhostTowerTileCoords.x < 0 || m_GhostTowerTileCoords.y < 0) {
			return;
		}
		
		_states.transform.translate(sf::Vector2f(static_cast<float>(m_GhostTowerTileCoords.x) + 0.5f, static_cast<float>(m_GhostTowerTileCoords.y) + 0.5f) * Definitions::TileSize);

		const float Radius{ 0.5f };
		sf::CircleShape c(Radius);
		c.setOrigin(Radius, Radius);
		c.setOutlineThickness(0.05f);
		c.setFillColor(m_ValidLocationForTowerGhost ? sf::Color::Green : sf::Color::Red);
		c.setOutlineColor(sf::Color::Black);
		_target.draw(c, _states);
	}

	// TODO: Replace this with LuaTowerParser lookupy??? or do that in the ui -> dispatcher -> this?
	bool TowerSpawnerService::beginGhostForPrototype(const ParsedTower& _prototype) {
		m_CurrentPrototype = _prototype;
		m_ShowingTowerGhost = true;
		updateGhostPosition(m_InputManager.getMousePosition());
		return true;
	}
	bool TowerSpawnerService::getShowingTowerGhost(void) const {
		return m_ShowingTowerGhost;
	}
	bool TowerSpawnerService::getValidLocationForTowerGhost(void) const {
		return m_ValidLocationForTowerGhost;
	}
	sf::Vector2i TowerSpawnerService::getGhostCoordinates(void) const {
		return m_GhostTowerTileCoords;
	}
	ParsedTower TowerSpawnerService::getGhostPrototype(void) const {
		return m_CurrentPrototype;
	}

	void TowerSpawnerService::updateGhostLocationValid(const ITowerPlaceableSurface* surface) {
		m_ValidLocationForTowerGhost = surface->canPlacePrototype(m_GhostTowerTileCoords, {});
	}

	void TowerSpawnerService::updateGhostPosition(const sf::Vector2i& _eventCoordinates) {
		if (_eventCoordinates.x < 0 || _eventCoordinates.y < 0) {
			m_GhostTowerTileCoords = { -1, -1 };
			return;
		}
		m_GhostTowerTileCoords = sf::Vector2i(sf::Vector2f(_eventCoordinates) / m_Config.getGameViewScale());

		const ITowerPlaceableSurface *surface = m_TowerPlaceableSurfaceService.getActiveSurface();
		if (surface == nullptr) {
			return;
		}

		if (static_cast<unsigned>(m_GhostTowerTileCoords.x) >= surface->getWidth()) {
			m_GhostTowerTileCoords.x = static_cast<int>(surface->getWidth()) - 1;
		}
		if (static_cast<unsigned>(m_GhostTowerTileCoords.y) >= surface->getHeight()) {
			m_GhostTowerTileCoords.y = static_cast<int>(surface->getHeight()) - 1;
		}

		updateGhostLocationValid(surface);
	}
	bool TowerSpawnerService::attemptPlacingGhost(const sf::Vector2i& _eventCoordinates) {
		updateGhostPosition(_eventCoordinates);

		if (!m_ValidLocationForTowerGhost) {
			return false;
		}

		if (prototypeSpawned) {
			prototypeSpawned(m_CurrentPrototype, m_GhostTowerTileCoords);
		}

		return true;
		
	}
	void TowerSpawnerService::reset(void) {
		m_CurrentPrototype = {};
		m_GhostTowerTileCoords = { -1, -1 };
		m_ShowingTowerGhost = false;
	}

}
