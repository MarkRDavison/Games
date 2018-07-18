#include <Castle/Scenes/GameScene.hpp>

#include <Castle/Components/SpriteComponent.hpp>

#include <iostream>
#include <Castle/Components/HealthComponent.hpp>

namespace castle {

	GameScene::GameScene(inf::TextureManager& _textureManager, inf::InputManager& _inputManager, CastleConfigurationManager& _castleConfigurationManager, CollisionSystem& _collisionSystem, KinematicSystem& _kinematicSystem, PlayerControlSystem& _playerControlSystem, PlayerInteractionSystem& _playerInteractionSystem, WaypointSystem& _waypointSystem, EntityPrototypeFactory& _entityPrototypeFactory) :
		inf::Scene("castle::GameScene"),
		m_CastleConfigurationManager(_castleConfigurationManager),
		m_InputManager(_inputManager),
		m_TextureManager(_textureManager),
		m_ActiveLevel(nullptr),
		m_CollisionSystem(_collisionSystem),
		m_KinematicSystem(_kinematicSystem),
		m_PlayerControlSystem(_playerControlSystem),
		m_PlayerInteractionSystem(_playerInteractionSystem),
		m_WaypointSystem(_waypointSystem),
		m_EntityPrototypeFactory(_entityPrototypeFactory) {

	}
	GameScene::~GameScene(void) {

	}

	void GameScene::update(float _delta) {
		ecs::EntityManager& em = m_ActiveLevel->getEntityManager();
		em.update(_delta);

		m_PlayerControlSystem.update(_delta, em);
		m_PlayerInteractionSystem.update(_delta, em);
		m_WaypointSystem.update(_delta, em);
		m_CollisionSystem.update(_delta, em, m_ActiveLevel);
		m_KinematicSystem.update(_delta, em);
		m_CollisionSystem.handleMovementStuff(_delta, m_ActiveLevel);

		em.refresh();
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		ecs::EntityManager& em = m_ActiveLevel->getEntityManager();
		if (m_PlayerControlSystem.handleEvent(_event, em)) {
			return true;
		}
		if (m_PlayerInteractionSystem.handleEvent(_event, em)) {
			return true;
		}
		if (m_WaypointSystem.handleEvent(_event, em)) {
			return true;
		}
		if (m_CollisionSystem.handleEvent(_event, em)) {
			return true;
		}
		if (m_KinematicSystem.handleEvent(_event, em)) {
			return true;
		}
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		sf::RenderStates levelStates(_states);
		levelStates.texture = &m_TextureManager.getTexture("terrain");
		_target.draw(reinterpret_cast<const sf::Drawable&>(*m_ActiveLevel), levelStates);
		m_ActiveLevel->getEntityManager().draw(_target, _states);
	}

	void GameScene::initialize(Level *_level) {
		std::cout << "Initialize castle::GameScene" << std::endl;
		if (m_ActiveLevel != nullptr) {
			delete m_ActiveLevel;
		}
		m_ActiveLevel = _level;
	}
	void GameScene::addPlayer(void) const {
		auto& e = m_ActiveLevel->getEntityManager().addEntity("Player");
		e.addGroup(EntityGroup::GPlayer);
		e.addGroup(EntityGroup::GKinematic);
		e.addGroup(EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(11.5f, 8.0f));
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture("player"), sf::IntRect(0, 0, 32, 48));
		e.addComponent<HealthComponent>(10, 10);
		e.addComponent<PlayerComponent>();
		e.addComponent<CollisionComponent>(sf::Vector2f(1.0f, 1.5f));
		e.getComponent<CollisionComponent>().canBeMovedByOthers = true;
		e.getComponent<CollisionComponent>().canMoveOthers = true;
	}
	void GameScene::addParsedLevel(const ParsedLevel& _parsedLevel) {
		m_ParsedLevels.emplace_back(_parsedLevel);
	}
	void GameScene::setActiveLevel(const std::string& _levelName) {
		const auto result = std::find_if(m_Levels.begin(), m_Levels.end(), [_levelName](const Level* _level) { return _level->getName() == _levelName; });
		if (result != m_Levels.end()) {
			Level *newLevel = *result;
			if (m_ActiveLevel != nullptr) {
				if (!ecs::EntityManager::swapEntityBetweenManagers(m_ActiveLevel->getEntityManager().getEntitiesByGroup(EntityGroup::GPlayer).front(), m_ActiveLevel->getEntityManager(), newLevel->getEntityManager())) {
					std::cout << "Failed to swap entity to new level " << _levelName << " from level " << m_ActiveLevel->getName() << std::endl;
					return;
				}
			}
			m_ActiveLevel = newLevel;
		}

		const auto parsedLevelResult = std::find_if(m_ParsedLevels.begin(), m_ParsedLevels.end(), [_levelName](const ParsedLevel& _parsedLevel) { return _parsedLevel.name == _levelName; });
		if (parsedLevelResult != m_ParsedLevels.end()) {
			Level *l = new Level();
			l->initialize(*parsedLevelResult, m_EntityPrototypeFactory);
			m_Levels.emplace_back(l);
			if (m_ActiveLevel != nullptr) {
				if (!ecs::EntityManager::swapEntityBetweenManagers(m_ActiveLevel->getEntityManager().getEntitiesByGroup(EntityGroup::GPlayer).front(), m_ActiveLevel->getEntityManager(), l->getEntityManager())) {
					std::cout << "Failed to swap entity to new level " << _levelName << " from level " << m_ActiveLevel->getName() << std::endl;
					return;
				}
			}
			m_ActiveLevel = l;
			std::cout << "Initialized new level and switched to it" << std::endl;
			return;
		}

		std::cout << "Failed to set active level " << _levelName << ", it wasn't made or initialized" << std::endl;
	}
}
