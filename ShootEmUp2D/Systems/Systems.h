#pragma once
#include <flecs.h>

#include "MovementSystem.h"
#include "RenderSystem.h"

inline void RegisterSystems(const flecs::world &ecsWorld) {
    MovementSystem(ecsWorld);
    RenderSystem(ecsWorld);
}
