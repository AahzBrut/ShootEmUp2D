#pragma once
#include <flecs.h>

#include "defs.h"
#include "Components/Bullet.h"
#include "Components/Position.h"

inline void BulletDestructionSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<const Position, Bullet>()
            .each([](const flecs::entity entity, const Position &p, Bullet) {
                if (p.x > WINDOW_WIDTH) entity.destruct();
            });
}
