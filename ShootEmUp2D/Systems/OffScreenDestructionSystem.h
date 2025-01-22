#pragma once
#include <flecs.h>

#include "defs.h"
#include "Components/Position.h"

inline void OffScreenDestructionSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<const Position>()
            .each([](const flecs::entity entity, const Position &p) {
                if (!entity.has<Player>() && (p.x > WINDOW_WIDTH || p.x < -100)) {
                    entity.destruct();
                }
            });
}
