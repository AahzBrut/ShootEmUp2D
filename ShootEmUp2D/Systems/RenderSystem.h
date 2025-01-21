#pragma once
#include <flecs.h>
#include <raylib.h>

#include "Components/Position.h"

inline void RenderSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<const Position, const Sprite>()
            .read<Position, Sprite>()
            .each([](const Position &p, const Sprite &s) {
                DrawTexture(*s.sprite, static_cast<int>(p.x), static_cast<int>(p.y), WHITE);
            });
}
