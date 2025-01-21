#pragma once
#include <flecs.h>

#include "BulletDestructionSystem.h"
#include "MovementSystem.h"
#include "PlayerControlSystem.h"
#include "RenderSystem.h"

inline void RegisterSystems(const flecs::world &ecsWorld, AssetManager& assetManager) {
    MovementSystem(ecsWorld);
    RenderSystem(ecsWorld);
    PlayerControlSystem(ecsWorld, assetManager);
    BulletDestructionSystem(ecsWorld);
}
