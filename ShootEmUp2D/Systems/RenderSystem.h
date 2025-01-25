#pragma once
#include <flecs.h>
#include <raylib.h>

#include "Components/Position.h"

inline void RenderSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<const Position, const Sprite>()
            .kind(flecs::OnStore)
            .each([](const Position &p, const Sprite &s) {
                if (s.sprite) DrawTexture(*s.sprite, toInt(p.x), toInt(p.y), WHITE);
            });
}
