# Utility
SET(UTILITY_HEADER_FILES ${UTILITY_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Utility/Collision.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/Colour.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/Hash.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/Orientation.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/PhysicsDebug.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/Signal.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/TestSignal.hpp
	${CMAKE_SOURCE_DIR}/include/Utility/TextHelpers.hpp
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
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Interfaces/IConfigurationManager.hpp

	${CMAKE_SOURCE_DIR}/include/Infrastructure/Application.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/ConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/FontManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/InputManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/LuaConsole.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/LuaManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scene.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/SceneManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/SplashScreen.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/TextureManager.hpp

	${CMAKE_SOURCE_DIR}/include/Infrastructure/DataStructures/Path.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/DataStructures/PathNode.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/DataStructures/ResourceBundle.hpp

	${CMAKE_SOURCE_DIR}/include/Infrastructure/Exceptions/SurfaceNotFoundException.hpp
	
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Gui/BasicButton.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Gui/TextBox.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Gui/UiElement.hpp

	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scenes/LuaConsoleScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Services/Interfaces/IResourceService.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Services/ResourceService.hpp

	${CMAKE_SOURCE_DIR}/include/Infrastructure/Services/IPathfindingService.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Services/PathfindingService.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Services/IPathSurface.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Services/ISurfaceService.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Services/SurfaceService.hpp
)
SET(INFRASTRUCTURE_SOURCE_FILES ${INFRASTRUCTURE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Application.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/ConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/FontManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/InputManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/LuaConsole.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/LuaManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Scene.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/SceneManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/SplashScreen.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/TextureManager.cpp
	
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Gui/BasicButton.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Gui/TextBox.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Gui/UiElement.cpp

	${CMAKE_SOURCE_DIR}/src/Infrastructure/Scenes/LuaConsoleScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Services/PathfindingService.cpp	
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Services/ResourceService.cpp	
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Services/SurfaceService.cpp

)

SET(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/src/EntityComponentSystem/EntityManagerTests.cpp

	${CMAKE_SOURCE_DIR}/test/src/Infrastructure/LuaConsoleTests.cpp
	
	${CMAKE_SOURCE_DIR}/test/src/Infrastructure/Services/PathfindingServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Infrastructure/Services/ResourceServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Infrastructure/Services/SurfaceServiceTests.cpp
)

SET(TEST_HEADER_FILES ${TEST_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Infrastructure/ConfigurationManagerMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Infrastructure/InputManagerMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Infrastructure/LuaManagerMock.hpp

	${CMAKE_SOURCE_DIR}/test/include/Mocks/Infrastructure/Services/ResourceServiceMock.hpp
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
	${CMAKE_SOURCE_DIR}/src/Hurricane/Infrastructure/Definitions.cpp
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

# Kingdom
SET(KINGDOM_HEADER_FILES ${KINGDOM_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/JobComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/JobPerformerComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/MovementComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/PathfindingComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/RenderableComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/SpriteComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Components/WaypointComponent.hpp

	${CMAKE_SOURCE_DIR}/include/Kingdom/DataStructures/LevelCell.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/DataStructures/ParsedLevel.hpp

	${CMAKE_SOURCE_DIR}/include/Kingdom/GameObjects/Level.hpp
	
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/Definitions.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/EntityFactory.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/KingdomConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Kingdom/Infrastructure/LuaLevelParser.hpp
	
	${CMAKE_SOURCE_DIR}/include/Kingdom/Scenes/GameScene.hpp
	
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
	
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Systems/MovementSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Systems/PathfindingSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Kingdom/Systems/WaypointSystemTests.cpp
)

# Intrusion
SET(INTRUSION_HEADER_FILES ${INTRUSION_HEADER_FILES} 
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/CircleComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/LifeComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/PathFollowComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/PositionComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/ProjectileComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/RenderableComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/SpriteComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/TowerFiringComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/TowerTargetComponent.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Components/TowerTargetingComponent.hpp
	
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/LevelCell.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/LifeBundle.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/ParsedEntity.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/ParsedLevel.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/ParsedProjectile.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/ParsedTower.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/ParsedWave.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/DataStructures/ResourceBundle.hpp

	${CMAKE_SOURCE_DIR}/include/Intrusion/GameObjects/Level.hpp
	
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/Interfaces/ITowerPlaceableSurface.hpp
	
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/EntityFactory.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/IntrusionConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/IntrusionDefinitions.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/IntrusionEntityGroups.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/LuaEntityParser.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/LuaLevelParser.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Infrastructure/LuaTowerParser.hpp
	
	${CMAKE_SOURCE_DIR}/include/Intrusion/Scenes/GameScene.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Scenes/GameUiScene.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Scenes/StartScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/ILevelResourceService.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/LevelResourceService.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/ITowerPlaceableSurfaceService.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/TowerPlaceableSurfaceService.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/ITowerSpawnerService.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/TowerSpawnerService.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/IWaveSpawnerService.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Services/WaveSpawnerService.hpp
	
	${CMAKE_SOURCE_DIR}/include/Intrusion/Systems/LifeSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Systems/PathFollowingSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Systems/ProjectileControlSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Systems/RenderSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Systems/TowerFiringSystem.hpp
	${CMAKE_SOURCE_DIR}/include/Intrusion/Systems/TowerTargetingSystem.hpp
)

SET(INTRUSION_SOURCE_FILES ${INTRUSION_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Intrusion/GameObjects/Level.cpp
	
	${CMAKE_SOURCE_DIR}/src/Intrusion/Infrastructure/EntityFactory.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Infrastructure/IntrusionConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Infrastructure/IntrusionDefinitions.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Infrastructure/LuaEntityParser.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Infrastructure/LuaLevelParser.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Infrastructure/LuaTowerParser.cpp
	
	${CMAKE_SOURCE_DIR}/src/Intrusion/Scenes/GameScene.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Scenes/GameUiScene.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Scenes/StartScene.cpp

	${CMAKE_SOURCE_DIR}/src/Intrusion/Services/LevelResourceService.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Services/TowerPlaceableSurfaceService.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Services/TowerSpawnerService.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Services/WaveSpawnerService.cpp
	
	${CMAKE_SOURCE_DIR}/src/Intrusion/Systems/LifeSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Systems/PathFollowingSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Systems/ProjectileControlSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Systems/RenderSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Systems/TowerFiringSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Intrusion/Systems/TowerTargetingSystem.cpp
)

SET(INTRUSION_TEST_HEADER_FILES ${INTRUSION_TEST_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Intrusion/Infrastructure/IntrusionConfigurationManagerMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Intrusion/Infrastructure/TowerPlaceableSurfaceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Intrusion/Infrastructure/TowerPlaceableSurfaceServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Intrusion/Services/LevelResourceServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Intrusion/Services/TowerSpawnerServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Intrusion/Services/WaveSpawnerServiceMock.hpp
)

SET(INTRUSION_TEST_SOURCE_FILES ${INTRUSION_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Services/LevelResourceServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Services/TowerPlaceableSurfaceServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Services/TowerSpawnerServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Services/WaveSpawnerServiceTests.cpp
	
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Systems/LifeSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Systems/PathFollowingSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Systems/ProjectileControlSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Systems/TowerFiringSystemTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Intrusion/Systems/TowerTargetingSystemTests.cpp
)

# Minesweeper
SET(MINESWEEPER_HEADER_FILES ${MINESWEEPER_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Minesweeper/DataStructures/BoardInteractionEvent.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/DataStructures/BoardInteractionState.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/DataStructures/Cell.hpp

	${CMAKE_SOURCE_DIR}/include/Minesweeper/Infrastructure/ConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Infrastructure/Definitions.hpp

	${CMAKE_SOURCE_DIR}/include/Minesweeper/GameObjects/GameBoard.hpp
	
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Scenes/ExitScene.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Scenes/GameScene.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Scenes/TitleScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/Interfaces/IBoardInitializationService.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/Interfaces/IBoardInteractionService.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/Interfaces/IBoardStatusService.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/Interfaces/ISceneChangeService.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/BoardInitializationService.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/BoardInteractionService.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/BoardStatusService.hpp
	${CMAKE_SOURCE_DIR}/include/Minesweeper/Services/SceneChangeService.hpp
)

SET(MINESWEEPER_SOURCE_FILES ${MINESWEEPER_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Infrastructure/ConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Infrastructure/Definitions.cpp

	${CMAKE_SOURCE_DIR}/src/Minesweeper/GameObjects/GameBoard.cpp
	
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Scenes/ExitScene.cpp
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Scenes/GameScene.cpp
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Scenes/TitleScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Services/BoardInitializationService.cpp
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Services/BoardInteractionService.cpp
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Services/BoardStatusService.cpp
	${CMAKE_SOURCE_DIR}/src/Minesweeper/Services/SceneChangeService.cpp
)

# Pollution
SET(POLLUTION_HEADER_FILES ${POLLUTION_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Pollution/DataStructures/AnimationData.hpp
	${CMAKE_SOURCE_DIR}/include/Pollution/DataStructures/BuildingData.hpp
	${CMAKE_SOURCE_DIR}/include/Pollution/DataStructures/WorldData.hpp
	
	${CMAKE_SOURCE_DIR}/include/Pollution/GameObjects/BuildingObject.hpp
	${CMAKE_SOURCE_DIR}/include/Pollution/GameObjects/WorldObject.hpp

	${CMAKE_SOURCE_DIR}/include/Pollution/Infrastructure/ConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Pollution/Infrastructure/Definitions.hpp
	
	${CMAKE_SOURCE_DIR}/include/Pollution/Scenes/GameScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Pollution/Services/Interfaces/IWorldInteractionService.hpp
	${CMAKE_SOURCE_DIR}/include/Pollution/Services/Interfaces/IWorldUpdateService.hpp

	${CMAKE_SOURCE_DIR}/include/Pollution/Services/WorldInteractionService.hpp
	${CMAKE_SOURCE_DIR}/include/Pollution/Services/WorldUpdateService.hpp
)

SET(POLLUTION_SOURCE_FILES ${POLLUTION_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Pollution/GameObjects/BuildingObject.cpp
	${CMAKE_SOURCE_DIR}/src/Pollution/GameObjects/WorldObject.cpp

	${CMAKE_SOURCE_DIR}/src/Pollution/Infrastructure/ConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Pollution/Infrastructure/Definitions.cpp
	
	${CMAKE_SOURCE_DIR}/src/Pollution/Scenes/GameScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Pollution/Services/WorldInteractionService.cpp
	${CMAKE_SOURCE_DIR}/src/Pollution/Services/WorldUpdateService.cpp
)

SET(POLLUTION_TEST_HEADER_FILES ${POLLUTION_TEST_HEADER_FILES}
)

SET(POLLUTION_TEST_SOURCE_FILES ${POLLUTION_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/src/Pollution/Services/WorldInteractionServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Pollution/Services/WorldUpdateServiceTests.cpp
)

# Driller 
SET(DRILLER_HEADER_FILES ${DRILLER_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Driller/Core/Game.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/BuildingData.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/BuildingInstance.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/BuildingPrototype.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/BuildingProvidedJob.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/JobCompleteDelegate.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/JobData.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/JobInstance.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/JobPrototype.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/GameCommand.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/ShuttleData.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/ShuttleInstance.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/ShuttlePrototype.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/TerrainData.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/TerrainTile.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/TerrainRow.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/WorkerData.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/WorkerInstance.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/DataStructures/WorkerPrototype.hpp

	${CMAKE_SOURCE_DIR}/include/Driller/GameObjects/GameObject.hpp

	${CMAKE_SOURCE_DIR}/include/Driller/Infrastructure/ConfigurationManager.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Infrastructure/Definitions.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Scenes/ExitScene.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Scenes/GameScene.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Scenes/GameUiScene.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Scenes/TitleScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IBuildingPlacementService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/ICostService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IGameCommandService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IIdentificationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IJobAllocationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IJobCreationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IJobCompletionService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IMarketService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IPrototypeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/ISceneChangeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IShuttleCargoService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IShuttleCompletionService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IShuttleCreationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IShuttleDepartureService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IShuttleUpdateService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/ITerrainAlterationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IWorkerClassService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IWorkerCreationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IWorkerRecruitmentService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/Interfaces/IWorkerUpdateService.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Services/BuildingPlacementService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/BuildingPrototypeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/CostService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/GameCommandService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/IdentificationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/JobAllocationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/JobCompletionService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/JobCreationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/JobPrototypeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/MarketService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/PrototypeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/SceneChangeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/ShuttleCargoService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/ShuttleCompletionService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/ShuttleCreationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/ShuttleDepartureService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/ShuttlePrototypeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/ShuttleUpdateService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/TerrainAlterationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/WorkerClassService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/WorkerCreationService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/WorkerPrototypeService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/WorkerRecruitmentService.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Services/WorkerUpdateService.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Views/View.hpp
	
	${CMAKE_SOURCE_DIR}/include/Driller/Views/BuildingView.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Views/JobView.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Views/ShuttleView.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Views/TerrainView.hpp
	${CMAKE_SOURCE_DIR}/include/Driller/Views/WorkerView.hpp
)

SET(DRILLER_SOURCE_FILES ${DRILLER_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Driller/Core/Game.cpp

	${CMAKE_SOURCE_DIR}/src/Driller/Infrastructure/ConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Infrastructure/Definitions.cpp
	
	${CMAKE_SOURCE_DIR}/src/Driller/Scenes/ExitScene.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Scenes/GameScene.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Scenes/GameUiScene.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Scenes/TitleScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Driller/Services/BuildingPlacementService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/BuildingPrototypeService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/CostService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/GameCommandService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/IdentificationService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/JobAllocationService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/JobCompletionService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/JobCreationService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/JobPrototypeService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/MarketService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/SceneChangeService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/ShuttleCargoService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/ShuttleCompletionService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/ShuttleCreationService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/ShuttleDepartureService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/ShuttlePrototypeService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/ShuttleUpdateService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/TerrainAlterationService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/WorkerClassService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/WorkerCreationService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/WorkerPrototypeService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/WorkerRecruitmentService.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Services/WorkerUpdateService.cpp
	
	${CMAKE_SOURCE_DIR}/src/Driller/Views/BuildingView.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Views/JobView.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Views/ShuttleView.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Views/TerrainView.cpp
	${CMAKE_SOURCE_DIR}/src/Driller/Views/WorkerView.cpp
)

SET(DRILLER_TEST_HEADER_FILES ${DRILLER_TEST_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/BuildingPlacementServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/CostServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/GameCommandServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/IdentificationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/JobAllocationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/JobCompletionServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/JobCreationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/MarketServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/PrototypeServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/ShuttleCargoServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/ShuttleCompletionServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/ShuttleCreationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/ShuttleDepartureServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/ShuttleUpdateServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/TerrainAlterationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/WorkerClassServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/WorkerCreationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/WorkerRecruitmentServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Driller/Services/WorkerUpdateServiceMock.hpp
)

SET(DRILLER_TEST_SOURCE_FILES ${DRILLER_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/src/Driller/Core/GameTests.cpp
	
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/BuildingPlacementServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/BuildingPrototypeServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/CostServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/GameCommandServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/JobAllocationServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/JobCompletionServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/JobCreationServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/MarketServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/SceneChangeServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/ShuttleCargoServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/ShuttleCompletionServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/ShuttleCreationServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/ShuttleDepartureServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/ShuttleUpdateServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/TerrainAlterationServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/WorkerClassServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/WorkerCreationServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/WorkerRecruitmentServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Driller/Services/WorkerUpdateServiceTests.cpp
)

# Sovereign

SET(SOVEREIGN_HEADER_FILES ${SOVEREIGN_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/include/Sovereign/Core/Definitions.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Core/Game.hpp
	
	${CMAKE_SOURCE_DIR}/include/Sovereign/DataStructures/ControlBindings.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/DataStructures/EntityContainedCell.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/DataStructures/EntityData.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/DataStructures/LevelChunk.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/DataStructures/LevelChunkCell.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/DataStructures/LevelData.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/DataStructures/MoveableEntity.hpp

	${CMAKE_SOURCE_DIR}/include/Sovereign/Enumerations/LogLevel.hpp
	
	${CMAKE_SOURCE_DIR}/include/Sovereign/Infrastructure/ConfigurationManager.hpp
	
	${CMAKE_SOURCE_DIR}/include/Sovereign/Scenes/ExitScene.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Scenes/GameScene.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Scenes/GameUiScene.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Scenes/TitleScene.hpp
	
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/ICollisionDetectionService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/ICollisionResponseService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/IEntityDataMutationService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/IEntityDataQueryService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/IEntityMovementService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/ILevelDataMutationService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/ILevelDataQueryService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/ILogService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/IPlayerControlService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/Interfaces/ISceneChangeService.hpp
	
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/CollisionDetectionService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/CollisionResponseService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/EntityDataMutationService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/EntityDataQueryService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/EntityMovementService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/LevelDataQueryService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/LogService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/PlayerControlService.hpp
	${CMAKE_SOURCE_DIR}/include/Sovereign/Services/SceneChangeService.hpp
)

SET(SOVEREIGN_SOURCE_FILES ${SOVEREIGN_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Sovereign/Core/Definitions.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Core/Game.cpp

	${CMAKE_SOURCE_DIR}/src/Sovereign/Infrastructure/ConfigurationManager.cpp
	
	${CMAKE_SOURCE_DIR}/src/Sovereign/Scenes/ExitScene.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Scenes/GameScene.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Scenes/GameUiScene.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Scenes/TitleScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/CollisionDetectionService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/CollisionResponseService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/EntityDataMutationService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/EntityMovementService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/EntityDataQueryService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/LevelDataQueryService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/LogService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/PlayerControlService.cpp
	${CMAKE_SOURCE_DIR}/src/Sovereign/Services/SceneChangeService.cpp
)

SET(SOVEREIGN_TEST_HEADER_FILES ${SOVEREIGN_TEST_HEADER_FILES}
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/CollisionDetectionServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/CollisionResponseServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/EntityDataMutationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/EntityDataQueryServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/EntityMovementServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/LevelDataMutationServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/LevelDataQueryServiceMock.hpp
	${CMAKE_SOURCE_DIR}/test/include/Mocks/Sovereign/Services/PlayerControlServiceMock.hpp
)

SET(SOVEREIGN_TEST_SOURCE_FILES ${SOVEREIGN_TEST_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/test/src/Sovereign/Services/CollisionDetectionServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Sovereign/Services/CollisionResponseServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Sovereign/Services/EntityDataMutationServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Sovereign/Services/EntityDataQueryServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Sovereign/Services/EntityMovementServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Sovereign/Services/LevelDataQueryServiceTests.cpp
	${CMAKE_SOURCE_DIR}/test/src/Sovereign/Services/PlayerControlServiceTests.cpp
)