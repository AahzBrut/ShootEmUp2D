#pragma once
#include <flecs.h>

#include "raylib.h"
#include "Components/Player.h"
#include "Components/Velocity.h"


inline void PlayerControlSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<const Player, Velocity>()
            .each([](const Player &p, Velocity &v) {
                v.x = v.y = 0.0f;

                if (IsKeyDown(KEY_W)) v.y = -p.speed;
                if (IsKeyDown(KEY_D)) v.x = p.speed;
                if (IsKeyDown(KEY_S)) v.y = p.speed;
                if (IsKeyDown(KEY_A)) v.x = -p.speed;
            });
}
