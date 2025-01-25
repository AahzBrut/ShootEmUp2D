#pragma once
#include <flecs.h>

#include "AssetManager/AssetManager.h"
#include "Utils/Random.h"


inline void SpawnExplosionSystem(const flecs::world &ecsWorld) {
    auto assetManager = ecsWorld.get_mut<AssetManager>();
    auto audioManager = ecsWorld.get_mut<AudioManager>();

    ecsWorld.system<const Explode>()
            .each([&ecsWorld, assetManager, audioManager](const flecs::entity entity, const Explode &explode) {
                const auto shotSound = assetManager->GetSoundEffect("explosion");
                audioManager->PlaySoundEffect(shotSound);

                for (auto i = 0; i < MAX_EXPLOSION_PARTICLES; i++) {
                    ecsWorld.entity().insert([&](ExplosionParticle &particle) {
                        particle = {
                            explode.x,
                            explode.y,
                            RandomRange(0.01, .5),
                            RandomRange(-100, 100),
                            RandomRange(-100, 100),
                            .7f,
                            RandomRange(1, 3),
                            0.f,
                            assetManager->GetTexture("explosion"),
                            Color(RandomIntRange(0, 255), RandomIntRange(0, 255), RandomIntRange(0, 255), 255)
                        };
                    });
                }

                entity.destruct();
            });
}
