#pragma once
#include <flecs.h>

#include "Components/Position.h"
#include "Components/Velocity.h"

inline void MovementSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<Position, const Velocity>()
            .each([](const flecs::iter &it, size_t, Position &p, const Velocity &v) {
                const auto deltaTime = it.delta_time();
                p.x += v.x * deltaTime;
                p.y += v.y * deltaTime;
            });
}
