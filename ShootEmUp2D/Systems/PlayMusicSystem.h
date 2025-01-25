#pragma once
#include <flecs.h>


inline void PlayMusicSystem(const flecs::world &ecsWorld) {
    auto assetManager = ecsWorld.get_mut<AssetManager>();

    ecsWorld.system()
        .run([assetManager](flecs::iter &_) {
            const auto music = assetManager->GetMusic("main-theme");
            UpdateMusicStream(*music);
    });
}
