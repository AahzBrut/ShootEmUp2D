#pragma once
#include <flecs.h>

#include "Components/Collider.h"

inline void AssetsLoadSystem(const flecs::world &ecsWorld) {
    ecsWorld.system()
            .kind(flecs::OnStart)
            .run([&](flecs::iter &_) {
                const auto assetManager = ecsWorld.get_mut<AssetManager>();
                assetManager->LoadTexture("player", "./assets/gfx/player.png");
                assetManager->LoadTexture("bullet", "./assets/gfx/playerBullet.png");
                assetManager->LoadTexture("enemy", "./assets/gfx/enemy.png");
                assetManager->LoadTexture("enemy-bullet", "./assets/gfx/alienBullet.png");
                assetManager->LoadTexture("background", "./assets/gfx/background.png");

                const auto playerSprite = assetManager->GetTexture("player");
                // ReSharper disable once CppExpressionWithoutSideEffects
                ecsWorld.entity()
                        .insert([&](Position &p, Velocity &v, Sprite &s, Player &pl, Collider &collider) {
                            p = {100, 100};
                            v = {60, 60};
                            s = {playerSprite};
                            pl = {100, 5, 0, 250};
                            collider = {
                                100, 100, static_cast<float>(playerSprite->width),
                                static_cast<float>(playerSprite->height), CollisionLayer::Player
                            };
                        });

                ecsWorld.entity()
                        .insert([&](Background &background) {
                            background = {assetManager->GetTexture("background"), 40.f, 0.f};
                        });

                LOG("Assets load complete.");
            });
}
