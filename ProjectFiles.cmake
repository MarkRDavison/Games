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
	${CMAKE_SOURCE_DIR}/include/Infrastructure/LuaManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/Scene.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/SceneManager.hpp
	${CMAKE_SOURCE_DIR}/include/Infrastructure/TextureManager.hpp
)
SET(INFRASTRUCTURE_SOURCE_FILES ${INFRASTRUCTURE_SOURCE_FILES}
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Application.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/ConfigurationManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/FontManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/InputManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/LuaManager.cpp
	${CMAKE_SOURCE_DIR}/src/Infrastructure/Scene.cpp
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
	${CMAKE_SOURCE_DIR}/src/Castle/Scenes/PlayerCollisionTestScene.cpp
	
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/CollisionSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/KinematicSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/PlayerControlSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/PlayerInteractionSystem.cpp
	${CMAKE_SOURCE_DIR}/src/Castle/Systems/WaypointSystem.cpp
)


SET(TEST_SOURCE_FILES ${TEST_SOURCE_FILES}
)

SET(TEST_HEADER_FILES ${TEST_HEADER_FILES}
)