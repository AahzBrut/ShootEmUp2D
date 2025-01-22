#pragma once
#include <flecs.h>

#include "Components/Position.h"
#include "Components/Velocity.h"

inline void MovementSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<Position, Collider, const Velocity>()
            .each([](const flecs::iter &it, size_t, Position &p, Collider &c, const Velocity &v) {
                const auto deltaTime = it.delta_time();
                p.x += v.x * deltaTime;
                p.y += v.y * deltaTime;
                c.x = p.x;
                c.y = p.y;
            });
}
