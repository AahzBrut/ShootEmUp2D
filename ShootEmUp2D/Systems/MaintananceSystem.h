#pragma once
#include <flecs.h>

#include "defs.h"
#include "AudioManager/AudioManager.h"

inline void MaintananceSystem(const flecs::world &ecsWorld) {
    auto audioManager = ecsWorld.get_mut<AudioManager>();
    ecsWorld.system()
            .interval(MAINTANANCE_TIMEOUT)
            .run([audioManager](const flecs::iter) {
                audioManager->Update();
            });
}
