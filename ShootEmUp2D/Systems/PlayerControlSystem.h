#pragma once
#include <flecs.h>

#include "raylib.h"
#include "Components/Player.h"
#include "Components/Velocity.h"


inline void PlayerControlSystem(const flecs::world &ecsWorld, AssetManager &assetManager) {
    ecsWorld.system<const Player, const Position, const Sprite, Velocity>()
            .each([&ecsWorld, &assetManager](const Player &p, const Position &pos, const Sprite &spr, Velocity &v) {
                v.x = v.y = 0.0f;

                if (IsKeyDown(KEY_W)) v.y = -p.speed;
                if (IsKeyDown(KEY_D)) v.x = p.speed;
                if (IsKeyDown(KEY_S)) v.y = p.speed;
                if (IsKeyDown(KEY_A)) v.x = -p.speed;

                if (IsKeyDown(KEY_SPACE)) {
                    const auto query = ecsWorld.query<Bullet>();
                    if (const auto bullet = query.find([](Bullet) { return true; }); !bullet) {
                        const auto bulletTexture = assetManager.GetTexture("bullet");
                        const auto bulletPosX = pos.x + spr.sprite->width / 2 - bulletTexture->width / 2;
                        const auto bulletPosY = pos.y + spr.sprite->height / 2 - bulletTexture->height / 2;

                        // ReSharper disable once CppExpressionWithoutSideEffects
                        ecsWorld.entity()
                                .insert([&](Position &bulletPos, Velocity &bulletVelocity, Sprite &s) {
                                    bulletPos = {bulletPosX, bulletPosY};
                                    bulletVelocity = {300, 0};
                                    s = {bulletTexture};
                                })
                                .add<Bullet>();
                    }
                }
            });
}
