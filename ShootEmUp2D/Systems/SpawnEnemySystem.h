#pragma once
#include <flecs.h>

#include "AssetManager/AssetManager.h"
#include "Components/AutoCanon.h"
#include "Components/Collider.h"
#include "Utils/Random.h"


inline void SpawnEnemy(const flecs::iter &it) {
    const auto assetManager = it.world().get_mut<AssetManager>();
    const auto enemyTexture = assetManager->GetTexture("enemy");
    const auto enemyBulletTexture = assetManager->GetTexture("enemy-bullet");
    const auto enemyYPos = RandomRange(0, WINDOW_HEIGHT - enemyTexture->height);

    it.world()
            .entity()
            .insert([&](Position &p, Velocity &v, Sprite &s, Collider &collider, AutoCanon &canon) {
                p = {WINDOW_WIDTH, enemyYPos};
                v = {-60, 0};
                s = {enemyTexture};
                collider = {p.x, p.y, static_cast<float>(enemyTexture->width), static_cast<float>(enemyTexture->height), CollisionLayer::Enemy};
                canon = { .2f, 1.f/.2f, 100, enemyBulletTexture, CollisionLayer::EnemyBullet};
            });
}

inline void SpawnEnemySystem(const flecs::world &ecsWorld) {
    ecsWorld.system("EnemySpawnSystem")
            .interval(ENEMY_SPAWN_TIMEOUT)
            .run(SpawnEnemy);
}
