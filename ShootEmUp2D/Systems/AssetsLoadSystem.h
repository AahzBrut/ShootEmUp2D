#pragma once
#include <flecs.h>

inline void AssetsLoadSystem(const flecs::world &ecsWorld) {
    ecsWorld.system()
            .kind(flecs::OnStart)
            .run([&](flecs::iter &_) {
                const auto assetManager = ecsWorld.get_mut<AssetManager>();
                assetManager->LoadTexture("player", "./assets/gfx/player.png");
                assetManager->LoadTexture("bullet", "./assets/gfx/playerBullet.png");
                assetManager->LoadTexture("enemy", "./assets/gfx/enemy.png");

                // ReSharper disable once CppExpressionWithoutSideEffects
                ecsWorld.entity()
                        .insert([&](Position &p, Velocity &v, Sprite &s, Player &pl) {
                            p = {100, 100};
                            v = {60, 60};
                            s = {assetManager->GetTexture("player")};
                            pl = {100, 5, 0, 250};
                        });
                LOG("Assets load complete.");
            });
}
