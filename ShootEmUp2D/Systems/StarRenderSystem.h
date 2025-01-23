#pragma once
#include <flecs.h>


inline void StartRenderSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<Star>()
            .kind(flecs::OnStore)
            .run([](flecs::iter &it) {
                const auto deltaTime = it.delta_time();

                BeginBlendMode(BLEND_ADDITIVE);

                while (it.next()) {
                    auto field = it.field<Star>(0);

                    for (const auto i: it) {
                        auto &[posX, posY, speed, size, texture, color] = field[i];
                        posX -= deltaTime * speed;
                        posX = posX < -50.0f ? WINDOW_WIDTH : posX;
                        const auto sprite = texture;

                        const auto srcRect = Rectangle{
                            0, 0,
                            static_cast<float>(sprite->width), static_cast<float>(sprite->height)
                        };
                        const auto dstRect = Rectangle{
                            posX, posY, sprite->width * size, sprite->height * size
                        };

                        DrawTexturePro(*sprite, srcRect, dstRect, {0, 0}, 0, color);
                    }
                }
                EndBlendMode();
            });
}
