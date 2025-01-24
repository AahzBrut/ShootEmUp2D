cmake_minimum_required(VERSION 3.30)
project(ShootEmUp2D)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
add_compile_definitions(FLECS_CPP_NO_AUTO_REGISTRATION)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v4.0.4
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib flecs)

add_executable(ShootEmUp2D
        ShootEmUp2D/main.cpp
        ShootEmUp2D/Application/Application.cpp
        ShootEmUp2D/Application/Application.h
        ShootEmUp2D/defs.h
        ShootEmUp2D/Components/Position.h
        ShootEmUp2D/Components/Velocity.h
        ShootEmUp2D/Systems/MovementSystem.h
        ShootEmUp2D/Systems/RenderSystem.h
        ShootEmUp2D/Components/Components.h
        ShootEmUp2D/Systems/Systems.h
        ShootEmUp2D/AssetManager/AssetManager.cpp
        ShootEmUp2D/AssetManager/AssetManager.h
        ShootEmUp2D/TypeDefs.h
        ShootEmUp2D/Logger.h
        ShootEmUp2D/Components/Sprite.h
        ShootEmUp2D/Components/Player.h
        ShootEmUp2D/Systems/PlayerControlSystem.h
        ShootEmUp2D/Components/Bullet.h
        ShootEmUp2D/Systems/OffScreenDestructionSystem.h
        ShootEmUp2D/Systems/SpawnEnemySystem.h
        ShootEmUp2D/Utils/Random.h
        ShootEmUp2D/Systems/AssetsLoadSystem.h
        ShootEmUp2D/Components/Collider.h
        ShootEmUp2D/Physics/CollisionLayersSettings.cpp
        ShootEmUp2D/Physics/CollisionLayersSettings.h
        ShootEmUp2D/Systems/CollisionDetectionSystem.h
        ShootEmUp2D/Components/AutoCanon.h
        ShootEmUp2D/Systems/EnemyFiringSystem.h
        ShootEmUp2D/Systems/RenderBackgroundSystem.h
        ShootEmUp2D/Components/Background.h
        ShootEmUp2D/Components/Star.h
        ShootEmUp2D/Systems/RenderStarsSystem.h
        ShootEmUp2D/Components/ExplosionParticle.h
        ShootEmUp2D/Components/Explode.h
        ShootEmUp2D/Systems/SpawnExplosionSystem.h
        ShootEmUp2D/Systems/RenderExplosionSystem.h
)

target_link_libraries(ShootEmUp2D PRIVATE raylib flecs_static)
target_include_directories(ShootEmUp2D PRIVATE ShootEmUp2D)

add_custom_target(COPY_ASSETS
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_LIST_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
)
add_dependencies(${CMAKE_PROJECT_NAME} COPY_ASSETS)
