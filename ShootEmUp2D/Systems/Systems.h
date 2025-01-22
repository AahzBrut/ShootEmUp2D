#pragma once
#include <flecs.h>

#include "Systems/MovementSystem.h"
#include "Systems/OffScreenDestructionSystem.h"
#include "Systems/PlayerControlSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/SpawnEnemySystem.h"

inline void RegisterSystems(const flecs::world &ecsWorld, AssetManager& assetManager) {
    MovementSystem(ecsWorld);
    RenderSystem(ecsWorld);
    PlayerControlSystem(ecsWorld, assetManager);
    OffScreenDestructionSystem(ecsWorld);
    SpawnEnemySystem(ecsWorld);
}
