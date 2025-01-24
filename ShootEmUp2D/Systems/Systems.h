#pragma once
#include <flecs.h>

#include "RenderBackgroundSystem.h"
#include "RenderStarsSystem.h"
#include "Systems/AssetsLoadSystem.h"
#include "Systems/CollisionDetectionSystem.h"
#include "Systems/EnemyFiringSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/OffScreenDestructionSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/SpawnEnemySystem.h"

inline void RegisterSystems(const flecs::world &ecsWorld) {
    AssetsLoadSystem(ecsWorld);
    MovementSystem(ecsWorld);
    RenderBackgroundSystem(ecsWorld);
    RenderStarsSystem(ecsWorld);
    RenderSystem(ecsWorld);
    PlayerControlSystem(ecsWorld);
    OffScreenDestructionSystem(ecsWorld);
    SpawnEnemySystem(ecsWorld);
    CollisionDetectionSystem(ecsWorld);
    EnemyFiringSystem(ecsWorld);
}
