#pragma once
#include <flecs.h>

#include "raylib.h"
#include "Components/Player.h"
#include "Components/Velocity.h"


inline void PlayerControlSystem(const flecs::world &ecsWorld) {
    auto assetManager = ecsWorld.get_mut<AssetManager>();
    auto audioManager = ecsWorld.get_mut<AudioManager>();
    ecsWorld.system<Player, const Position, const Sprite, Velocity>()
            .each([&ecsWorld, assetManager, audioManager](const flecs::iter &it, size_t, Player &p, const Position &pos,
                                                          const Sprite &spr, Velocity &v) {
                v.x = v.y = 0.0f;
                if (p.fireDelay > 0.f) {
                    const auto deltaTime = it.delta_time();
                    p.fireDelay -= deltaTime;
                    if (p.fireDelay <= 0.f) p.fireDelay = 0.f;
                }

                if (IsKeyDown(KEY_W)) v.y = -p.speed;
                if (IsKeyDown(KEY_D)) v.x = p.speed;
                if (IsKeyDown(KEY_S)) v.y = p.speed;
                if (IsKeyDown(KEY_A)) v.x = -p.speed;

                if (IsKeyDown(KEY_SPACE)) {
                    if (p.fireDelay <= 0.0f) {
                        p.fireDelay = 1.0f / p.fireRate;

                        const auto shotSound = assetManager->GetSoundEffect("laser");
                        audioManager->PlaySoundEffect(shotSound);

                        const auto bulletTexture = assetManager->GetTexture("bullet");
                        const auto bulletPosX = pos.x + toFloat(spr.sprite->width) - toFloat(bulletTexture->width) / 2;
                        const auto bulletPosY = pos.y + toFloat(spr.sprite->height) / 2 - toFloat(bulletTexture->height)
                                                / 2;

                        // ReSharper disable once CppExpressionWithoutSideEffects
                        ecsWorld.entity()
                                .insert([&](Position &bulletPos, Velocity &bulletVelocity, Sprite &sprite,
                                            Collider &collider) {
                                    bulletPos = {bulletPosX, bulletPosY};
                                    bulletVelocity = {p.bulletSpeed, 0};
                                    sprite = {bulletTexture};
                                    collider = {
                                        bulletPosX, bulletPosY, toFloat(bulletTexture->width),
                                        toFloat(bulletTexture->height), CollisionLayer::PlayerBullet
                                    };
                                })
                                .add<Bullet>();
                    }
                }
            });
}
