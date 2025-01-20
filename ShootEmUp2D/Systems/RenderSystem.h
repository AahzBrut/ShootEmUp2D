#pragma once
#include <flecs.h>
#include <raylib.h>

#include "Components/Position.h"

inline void RenderSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<const Position>()
            .each([](const Position &p) {
                DrawRectangle(static_cast<int>(p.x), static_cast<int>(p.y), 20, 20, WHITE);
            });
}
