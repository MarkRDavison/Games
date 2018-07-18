#ifndef INCLUDED_CASTLE_INFRASTRUCTURE_ENTITY_PROTOTYPE_FACTORY_HPP_
#define INCLUDED_CASTLE_INFRASTRUCTURE_ENTITY_PROTOTYPE_FACTORY_HPP_

#include <EntityComponentSystem/EntityManager.hpp>
#include <Castle/DataStructures/ParsedEntity.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace castle {
	class EntityPrototypeFactory {
	public:
		EntityPrototypeFactory(inf::TextureManager& _textureManager);
		virtual ~EntityPrototypeFactory(void);

		virtual void createEntityFromPrototype(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity);

		void createCoinEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const;
		void createLadderEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const;
		void createFlameEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const;
		void createMovingPlatformEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const;
		void createMovingPlayerEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const;
		void createLevelTransitionEntity(ecs::EntityManager& _entityManager, const ParsedEntity& _parsedEntity) const;
	protected:
		inf::TextureManager& m_TextureManager;
	};
}

#endif // INCLUDED_CASTLE_INFRASTRUCTURE_ENTITY_PROTOTYPE_FACTORY_HPP_