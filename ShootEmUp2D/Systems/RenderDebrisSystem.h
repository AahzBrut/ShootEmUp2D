#pragma once
#include <flecs.h>


inline void RenderDebrisSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<Debris>()
            .kind(flecs::OnStore)
            .each([](const flecs::iter &it, const size_t index, Debris &debris) {
                const auto deltaTime = it.delta_time();
                debris.position.x += deltaTime * debris.velocity.x;
                debris.position.y += deltaTime * debris.velocity.y;
                debris.rotation += deltaTime * debris.rotationSpeed;
                debris.lifeTimeLeft -= deltaTime;
                if (debris.lifeTimeLeft >= 0) {
                    DrawTexturePro(
                        *debris.texture,
                        debris.textureRect,
                        Rectangle(debris.position.x, debris.position.y, debris.textureRect.width, debris.textureRect.height),
                        Vector2(debris.textureRect.width / 2, debris.textureRect.height / 2),
                        debris.rotation,
                        WHITE
                        );
                } else {
                    it.entity(index).destruct();
                }
            });
}
