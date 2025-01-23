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

                        const auto srcRect = Rectangle(0, 0, sprite->width, sprite->height);
                        const auto dstRect = Rectangle(posX, posY,
                                                       static_cast<int>(sprite->width * size),
                                                       static_cast<int>(sprite->height * size));

                        if (sprite) {
                            DrawTexturePro(*sprite, srcRect, dstRect, {0, 0}, 0, color);
                        }
                    }
                }
                EndBlendMode();
            });
}
