#pragma once
#include <flecs.h>

#include "Components/Collider.h"
#include "Utils/Random.h"


inline void SpawnPlayer(const flecs::world &ecsWorld, AssetManager &assetManager) {
    const auto playerSprite = assetManager.GetTexture("player");
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
}

inline void SpawnBackground(const flecs::world &ecsWorld, AssetManager &assetManager) {
    ecsWorld.entity()
            .insert([&](Background &background) {
                background = {assetManager.GetTexture("background"), 40.f, 0.f};
            });
}

inline void SpawnStars(const flecs::world &ecsWorld, AssetManager &assetManager) {
    for (auto i = 0; i < MAX_STARS; ++i) {
        const auto posX = RandomRange(0, WINDOW_WIDTH);
        const auto posY = RandomRange(0, WINDOW_HEIGHT);
        ecsWorld.entity()
                .insert([&](Star &star) {
                    const auto starSpeed = RandomRange(10, 100);
                    star = {
                        posX, posY,
                        starSpeed,
                        RandomRange(.01, .1),
                        assetManager.GetTexture("explosion"),
                        Color(
                            RandomIntRange(50, 255),
                            RandomIntRange(50, 255),
                            RandomIntRange(50, 255),
                            toInt(255 * starSpeed / 100))
                    };
                });
    }
}

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
                assetManager->LoadTexture("explosion", "./assets/gfx/explosion.png");

                assetManager->LoadMusic("main-theme", "./assets/music/Mercury.ogg");

                assetManager->LoadSound("explosion", "./assets/sound/Explosion.ogg");
                assetManager->LoadSound("laser", "./assets/sound/Laser.ogg");
                assetManager->LoadSound("laser-gun", "./assets/sound/LaserGun.ogg");
                assetManager->LoadSound("notification", "./assets/sound/Notification.ogg");
                assetManager->LoadSound("shotgun", "./assets/sound/Shotgun.ogg");

                SpawnPlayer(ecsWorld, *assetManager);
                SpawnBackground(ecsWorld, *assetManager);
                SpawnStars(ecsWorld, *assetManager);

                LOG("Assets load complete.");
            });
}
