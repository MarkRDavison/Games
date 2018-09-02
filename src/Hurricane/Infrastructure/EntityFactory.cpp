#include <Hurricane/Infrastructure/EntityFactory.hpp>
#include <Hurricane/Components/MovementComponent.hpp>
#include <Hurricane/Infrastructure/Definitions.hpp>
#include <Hurricane/Components/PositionComponent.hpp>
#include <Hurricane/Components/PlayerComponent.hpp>
#include <Hurricane/Components/HealthComponent.hpp>
#include <Hurricane/Components/SpriteComponent.hpp>
#include <Hurricane/Components/CollisionComponent.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>
#include <Hurricane/Components/DropComponent.hpp>
#include <Hurricane/Components/PickupComponent.hpp>
#include <iostream>

namespace hur {

	EntityFactory::EntityFactory(inf::TextureManager& _textureManager, LuaDataParser& _luaDataParser) :
		m_TextureManager(_textureManager),
		m_LuaDataParser(_luaDataParser) {
		
	}
	EntityFactory::~EntityFactory(void) {
		
	}

	ecs::Entity& EntityFactory::createPlayer(ecs::EntityManager& _entityManager) const {
		ecs::Entity& e = _entityManager.addEntity("Player");
		e.addGroup(hurr::EntityGroup::GPlayer);
		e.addGroup(hurr::EntityGroup::GKinematic);
		e.addGroup(hurr::EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(sf::Vector2f(10.0f, 15.0f));
		e.addComponent<MovementComponent>();
		e.addComponent<PlayerComponent>();
		e.addComponent<HealthComponent>(5, 20, Definitions::PlayerTeam);
		const sf::Vector2f size{ 99.0f, 75.0f };
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture(Definitions::BluePlayerShip), sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		e.addComponent<CollisionComponent>(sf::Vector2f(size.x / 64.0f, size.y / 64.0f));
		return e;
	}
	ecs::Entity& EntityFactory::createBlackEnemy(ecs::EntityManager& _entityManager, int _index, const sf::Vector2f& _position) const {
		ecs::Entity& e = _entityManager.addEntity("Black_Enemy_" + std::to_string(_index));
		e.addGroup(hurr::EntityGroup::GEnemy);
		e.addGroup(hurr::EntityGroup::GKinematic);
		e.addGroup(hurr::EntityGroup::GCollideable);
		e.addComponent<PositionComponent>(_position);
		e.addComponent<MovementComponent>();
		e.addComponent<HealthComponent>(2, 2, Definitions::EnemyTeam);

		std::string textureName;
		sf::Vector2f size{};
		switch (_index) {
		case 1:
			textureName = hur::Definitions::EnemyShipBlack1;
			size = { 93.0f, 84.0f };
			break;
		case 2:
			textureName = hur::Definitions::EnemyShipBlack2;
			size = { 104.0f, 84.0f };
			break;
		case 3:
			textureName = hur::Definitions::EnemyShipBlack3;
			size = { 103.0f, 84.0f };
			break;
		case 4:
			textureName = hur::Definitions::EnemyShipBlack4;
			size = { 82.0f, 84.0f };
			break;
		default:
			textureName = hur::Definitions::EnemyShipBlack5;
			size = { 97.0f, 84.0f };
			break;
		}

		e.addComponent<SpriteComponent>(m_TextureManager.getTexture(textureName), sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		e.addComponent<CollisionComponent>(sf::Vector2f(size.x / 64.0f, size.y / 64.0f));
		e.addComponent<DropComponent>(Definitions::BlackEnemyDropTable);

		return e;
	}
	ecs::Entity& EntityFactory::createBolt(ecs::EntityManager& _entityManager, const std::string& _bolt, const sf::Vector2f& _position) const {
		ecs::Entity& e = _entityManager.addEntity(_bolt);
		e.addGroup(hurr::EntityGroup::GKinematic);
		e.addGroup(hurr::EntityGroup::GCollideable);
		e.addGroup(hurr::EntityGroup::GPickup);
		e.addComponent<PickupComponent>();
		e.addComponent<PositionComponent>(_position);
		e.addComponent<MovementComponent>().velocity.y = 5.0f;
		const sf::Vector2f size{19.0f, 30.0f};
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture(_bolt), sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		e.addComponent<CollisionComponent>(sf::Vector2f(size.x / 64.0f, size.y / 64.0f));
		return e;
	}
	ecs::Entity& EntityFactory::createPill(ecs::EntityManager& _entityManager, const std::string& _pill, const sf::Vector2f& _position) const {
		ecs::Entity& e = _entityManager.addEntity(_pill);
		e.addGroup(hurr::EntityGroup::GKinematic);
		e.addGroup(hurr::EntityGroup::GCollideable);
		e.addGroup(hurr::EntityGroup::GPickup);
		PickupComponent& puc = e.addComponent<PickupComponent>();
		if (_pill == Definitions::PillRed) {
			puc.effect = PickupEffect::Health;
		}
		else if (_pill == Definitions::PillBlue) {
			puc.effect = PickupEffect::Shields;
		}
		else if (_pill == Definitions::PillYellow) {
			puc.effect = PickupEffect::Armour;
		}
		puc.integerAmount = 5;
		e.addComponent<PositionComponent>(_position);
		e.addComponent<MovementComponent>().velocity.y = 5.0f;
		const sf::Vector2f size{ 22.0f, 21.0f };
		e.addComponent<SpriteComponent>(m_TextureManager.getTexture(_pill), sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
		e.addComponent<CollisionComponent>(sf::Vector2f(size.x / 64.0f, size.y / 64.0f));
		return e;
	}

	void EntityFactory::createPotentialDropFromDropTable(ecs::EntityManager& _entityManager, const std::string& _dropTable, const sf::Vector2f& _position) const {
		if (!m_LuaDataParser.hasDropTable(_dropTable)) {
			return;
		}

		const DropTable& dropTable = m_LuaDataParser.getDropTable(_dropTable);

		const int chance = rand() % 100;
		std::cout << "Chance: " << chance << std::endl;
		// TODO: This needs to be better, and sort by rarest first etc
		for (const auto& cAndE : dropTable.chancesAndEntities) {
			if (chance < cAndE.first) {
				
				for (const auto& s : cAndE.second) {
					if (s == Definitions::BoltBronze ||
						s == Definitions::BoltSilver ||
						s == Definitions::BoltGold) {
						createBolt(_entityManager, s, _position);
					} else if (s == Definitions::PillBlue ||
							   s == Definitions::PillGreen ||
							   s == Definitions::PillRed ||
							   s == Definitions::PillYellow) {
						createPill(_entityManager, s, _position);
					}
				}
				return;
			}
		}
	}

}
