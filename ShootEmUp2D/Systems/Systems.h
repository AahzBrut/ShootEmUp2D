#pragma once
#include <flecs.h>

#include "AssetsLoadSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/OffScreenDestructionSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/SpawnEnemySystem.h"

inline void RegisterSystems(const flecs::world &ecsWorld) {
    MovementSystem(ecsWorld);
    RenderSystem(ecsWorld);
    PlayerControlSystem(ecsWorld);
    OffScreenDestructionSystem(ecsWorld);
    SpawnEnemySystem(ecsWorld);
    AssetsLoadSystem(ecsWorld);
}
