#pragma once
#include <flecs.h>

#include "Components/Background.h"


inline void RenderBackgroundSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<Background>()
        .kind(flecs::OnStore)
        .each([](const flecs::iter &it, size_t, Background &background) {
            const auto deltaTime = it.delta_time();
            const auto sprite = background.sprite;

            background.offset += deltaTime * background.scrollSpeed;

            const auto srcRect = Rectangle(
                background.offset,
                0,
                WINDOW_WIDTH,
                WINDOW_HEIGHT
            );

            constexpr auto dstRect = Rectangle(
                0,
                0,
                WINDOW_WIDTH,
                WINDOW_HEIGHT);


            if (sprite) DrawTexturePro(*sprite, srcRect, dstRect, {0,0}, 0, WHITE);
        });
}
