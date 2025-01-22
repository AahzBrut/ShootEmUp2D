#pragma once
#include <flecs.h>

#include "AssetManager/AssetManager.h"
#include "Utils/Random.h"


inline void SpawnEnemy(const flecs::iter &it) {
    const auto assetManager = it.world().get_mut<AssetManager>();
    const auto enemyTexture = assetManager->GetTexture("enemy");
    const auto enemyYPos = RandomRange(0, WINDOW_HEIGHT - enemyTexture->height);

    it.world()
            .entity()
            .insert([&](Position &p, Velocity &v, Sprite &s) {
                p = {WINDOW_WIDTH, enemyYPos};
                v = {-60, 0};
                s = {assetManager->GetTexture("enemy")};
            });
}

inline void SpawnEnemySystem(const flecs::world &ecsWorld) {
    ecsWorld.system("EnemySpawnSystem")
            .interval(ENEMY_SPAWN_TIMEOUT)
            .run(SpawnEnemy);
}
