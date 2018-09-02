# Utility
SET(UTILITY_HEADER_FILES ${UTILITY_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Utility/Collision.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/Colour.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/Orientation.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/PhysicsDebug.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/VectorMath.hpp
)
SET(UTILITY_SOURCE_FILES ${UTILITY_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Utility/Collision.cpp
	${CMAKE_SOURCE_DIR}/src/Utility/Colour.cpp
	${CMAKE_SOURCE_DIR}/src/Utility/PhysicsDebug.cpp
	${CMAKE_SOURCE_DIR}/src/Utility/VectorMath.cpp
)

# Entity Component System

SET(ENTITY_COMPONENT_SYSTEM_HEADER_FILES ${ENTITY_COMPONENT_SYSTEM_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/EntityComponentSystem/Component.hpp
	${CMAKE_SOURCE_DIR}/include/EntityComponentSystem/ECS.hpp
	${CMAKE_SOURCE_DIR}/include/EntityComponentSystem/Entity.hpp
	${CMAKE_SOURCE_DIR}/include/EntityComponentSystem/EntityManager.hpp
	${CMAKE_SOURCE_DIR}/include/EntityComponentSystem/System.hpp
)

SET(ENTITY_COMPONENT_SYSTEM_SOURCE_FILES ${ENTITY_COMPONENT_SYSTEM_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/EntityComponentSystem/Entity.cpp
	${CMAKE_SOURCE_DIR}/src/EntityComponentSystem/EntityManager.cpp
)

# Infrastructure
SET(INFRASTRUCURE_HEADER_FILES ${INFRASTRUCURE_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Application.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/ConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/FontManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/InputManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/LuaConsole.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/LuaManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scene.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scenes/LuaConsoleScene.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/SceneManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/TextureManager.hpp
)
SET(INFRASTRUCTURE_SOURCE_FILES ${INFRASTRUCTURE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Application.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/ConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/FontManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/InputManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/LuaConsole.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/LuaManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Scene.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Scenes/LuaConsoleScene.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/SceneManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/TextureManager.cpp
)

# Arkanoid
SET(ARKANOID_HEADER_FILES ${ARKANOID_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Arkanoid/Components/CircleComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Arkanoid/Components/PhysicsComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Arkanoid/Components/PlayerPaddleControlComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Arkanoid/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Arkanoid/Components/RectangleComponent.hpp

	${CMAKE_SOURCE_DIR}/include/Arkanoid/Infrastructure/ArkanoidConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Arkanoid/Infrastructure/Definitions.hpp

	${CMAKE_SOURCE_DIR}/include/Arkanoid/Scenes/GameScene.hpp
)
SET(ARKANOID_HEADER_FILES ${ARKANOID_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/src/Arkanoid/Infrastructure/ArkanoidConfigurationManager.cpp

	${CMAKE_SOURCE_DIR}/src/Arkanoid/Scenes/GameScene.cpp
)

# Snake
SET(SNAKE_HEADER_FILES ${SNAKE_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Snake/Components/AppleComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Snake/Components/CircleComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Snake/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Snake/Components/SnakeComponent.hpp

	${CMAKE_SOURCE_DIR}/include/Snake/Infrastructure/SnakeConfigurationManager.hpp

	${CMAKE_SOURCE_DIR}/include/Snake/Scenes/GameScene.hpp
)
SET(SNAKE_SOURCE_FILES ${SNAKE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Snake/Infrastructure/SnakeConfigurationManager.cpp

	${CMAKE_SOURCE_DIR}/src/Snake/Scenes/GameScene.cpp
)

# Pacman
SET(PACMAN_HEADER_FILES ${PACMAN_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Pacman/Components/GhostAnimationComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Pacman/Components/GhostControlComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Pacman/Components/PacmanAnimationComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Pacman/Components/PacmanPlayerControlComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Pacman/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Pacman/Components/SpriteComponent.hpp
	
	${CMAKE_SOURCE_DIR}/include/Pacman/GameObjects/Board.hpp
	
	${CMAKE_SOURCE_DIR}/include/Pacman/Infrastructure/BoardFactory.hpp
	${CMAKE_SOURCE_DIR}/include/Pacman/Infrastructure/Definitions.hpp
	${CMAKE_SOURCE_DIR}/include/Pacman/Infrastructure/PacmanConfigurationManager.hpp

	${CMAKE_SOURCE_DIR}/include/Pacman/Scenes/GameScene.hpp
)
SET(PACMAN_SOURCE_FILES ${PACMAN_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Pacman/GameObjects/Board.cpp
	
	${CMAKE_SOURCE_DIR}/src/Pacman/Infrastructure/BoardFactory.cpp
	${CMAKE_SOURCE_DIR}/src/Pacman/Infrastructure/PacmanConfigurationManager.cpp

	${CMAKE_SOURCE_DIR}/src/Pacman/Scenes/GameScene.cpp
)

# Castle
SET(CASTLE_HEADER_FILES ${CASTLE_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Castle/Components/PlayerComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/SpriteComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/RectangleComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/TimerComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/InteractableComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/HealthComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/CollisionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/WaypointComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Components/LevelTransitionComponent.hpp

	${CMAKE_SOURCE_DIR}/include/Castle/GameObjects/Level.hpp
	
	${CMAKE_SOURCE_DIR}/include/Castle/Infrastructure/AutoPlayerInputManager.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Infrastructure/CastleConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Infrastructure/EntityGroups.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Infrastructure/EntityPrototypeFactory.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Infrastructure/LuaLevelParser.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Infrastructure/LevelTransitionCoordinator.hpp
	
	${CMAKE_SOURCE_DIR}/include/Castle/DataStructures/LevelCell.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/DataStructures/ParsedEntity.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/DataStructures/ParsedLevel.hpp
	
	${CMAKE_SOURCE_DIR}/include/Castle/Scenes/GameScene.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Scenes/DebugOverlayScene.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Scenes/PlayerCollisionTestScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Castle/Systems/System.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Systems/CollisionSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Systems/KinematicSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Systems/PlayerControlSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Systems/PlayerInteractionSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Castle/Systems/WaypointSystem.hpp
)
SET(CASTLE_SOURCE_FILES ${CASTLE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Castle/GameObjects/Level.cpp
	
	${CMAKE_SOURCE_DIR}/src/Castle/Infrastructure/AutoPlayerInputManager.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Infrastructure/CastleConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Infrastructure/EntityPrototypeFactory.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Infrastructure/LuaLevelParser.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Infrastructure/LevelTransitionCoordinator.cpp
	
	${CMAKE_SOURCE_DIR}/src/Castle/Scenes/GameScene.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Scenes/DebugOverlayScene.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Scenes/PlayerCollisionTestScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/CollisionSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/KinematicSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/PlayerControlSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/PlayerInteractionSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/WaypointSystem.cpp
)

# Hurricane
SET(HURRICANE_HEADER_FILES ${HURRICANE_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/CollisionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/DamageComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/DropComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/HealthComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/MovementComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/PickupComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/PlayerComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/ProjectileComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Components/SpriteComponent.hpp
	
	${CMAKE_SOURCE_DIR}/include/Hurricane/Infrastructure/Definitions.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Infrastructure/EntityFactory.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Infrastructure/EntityGroups.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Infrastructure/HurricaneConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Infrastructure/LuaDataParser.hpp
	
	${CMAKE_SOURCE_DIR}/include/Hurricane/Objects/DropTable.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Objects/Level.hpp
	
	${CMAKE_SOURCE_DIR}/include/Hurricane/Scenes/DebugOverlayGameScene.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Scenes/GameScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Hurricane/Systems/CollisionSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Systems/KinematicSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Systems/PickupControlSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Systems/PlayerControlSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Hurricane/Systems/ProjectileControlSystem.hpp
)
SET(HURRICANE_SOURCE_FILES ${HURRICANE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Hurricane/Infrastructure/EntityFactory.cpp
	${CMAKE_SOURCE_DIR}/src/Hurricane/Infrastructure/HurricaneConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Hurricane/Infrastructure/LuaDataParser.cpp

	${CMAKE_SOURCE_DIR}/src/Hurricane/Objects/Level.cpp
	
	${CMAKE_SOURCE_DIR}/src/Hurricane/Scenes/DebugOverlayGameScene.cpp
	${CMAKE_SOURCE_DIR}/src/Hurricane/Scenes/GameScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Hurricane/Systems/CollisionSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Hurricane/Systems/KinematicSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Hurricane/Systems/PickupControlSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Hurricane/Systems/PlayerControlSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Hurricane/Systems/ProjectileControlSystem.cpp
)


SET(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/src/Infrastructure/LuaConsoleTests.cpp
)

SET(TEST_HEADER_FILES ${TEST_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Infrastructure/InputManagerMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Infrastructure/LuaManagerMock.hpp
)

# Kingdom
SET(KINGDOM_HEADER_FILES ${KINGDOM_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/MovementComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/PathfindingComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/RenderableComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/SpriteComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/WaypointComponent.hpp

	${CMAKE_SOURCE_DIR}/include/Kingdom/DataStructures/LevelCell.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/DataStructures/ParsedLevel.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/DataStructures/PathNode.hpp

	${CMAKE_SOURCE_DIR}/include/Kingdom/Exceptions/SurfaceNotFoundException.hpp

	${CMAKE_SOURCE_DIR}/include/Kingdom/GameObjects/Level.hpp
	
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/Definitions.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/EntityFactory.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/KingdomConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/LuaLevelParser.hpp
	
	${CMAKE_SOURCE_DIR}/include/Kingdom/Scenes/GameScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Kingdom/Services/IPathfindingService.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Services/PathfindingService.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Services/IPathSurface.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Services/ISurfaceService.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Services/SurfaceService.hpp
	
	${CMAKE_SOURCE_DIR}/include/Kingdom/Systems/MovementSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Systems/PathfindingSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Systems/RenderSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Systems/WaypointSystem.hpp
)

SET(KINGDOM_SOURCE_FILES ${KINGDOM_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Kingdom/GameObjects/Level.cpp
	
	${CMAKE_SOURCE_DIR}/src/Kingdom/Infrastructure/Definitions.cpp
	${CMAKE_SOURCE_DIR}/src/Kingdom/Infrastructure/EntityFactory.cpp
	${CMAKE_SOURCE_DIR}/src/Kingdom/Infrastructure/KingdomConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Kingdom/Infrastructure/LuaLevelParser.cpp
	
	${CMAKE_SOURCE_DIR}/src/Kingdom/Scenes/GameScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Kingdom/Services/PathfindingService.cpp	
	${CMAKE_SOURCE_DIR}/src/Kingdom/Services/SurfaceService.cpp
	
	${CMAKE_SOURCE_DIR}/src/Kingdom/Systems/MovementSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Kingdom/Systems/PathfindingSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Kingdom/Systems/RenderSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Kingdom/Systems/WaypointSystem.cpp
)

SET(KINGDOM_TEST_HEADER_FILES ${KINGDOM_TEST_HEADER_FILES} 
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Kingdom/Services/PathfindingServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Kingdom/Services/PathSurfaceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Kingdom/Services/SurfaceServiceMock.hpp
)
SET(KINGDOM_TEST_SOURCE_FILES ${KINGDOM_TEST_SOURCE_FILES} 
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/GameObjects/LevelTests.cpp
	
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Services/PathfindingServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Services/SurfaceServiceTests.cpp
	
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Systems/MovementSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Systems/PathfindingSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Systems/WaypointSystemTests.cpp
)