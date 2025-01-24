#pragma once
#include <flecs.h>

#include "raylib.h"
#include "Components/ExplosionParticle.h"


inline void RenderExplosionSystem(const flecs::world &ecsWorld) {
    ecsWorld.system<ExplosionParticle>()
            .kind(flecs::OnStore)
            .run([](flecs::iter &it) {
                BeginBlendMode(BLEND_ADDITIVE);
                const auto deltaTime = it.delta_time();

                while (it.next()) {
                    auto field = it.field<ExplosionParticle>(0);

                    for (const auto entityIndex: it) {
                        auto &particle = field[entityIndex];
                        particle.x += particle.dx * deltaTime;
                        particle.y += particle.dy * deltaTime;
                        particle.currentLifetime += deltaTime;

                        if (particle.currentLifetime < particle.maxLifetime) {
                            const auto alpha = toUChar(255 * (particle.currentLifetime / particle.maxLifetime));
                            const auto originX = particle.size * toFloat(particle.texture->width) * .5f;
                            const auto originY = particle.size * toFloat(particle.texture->height) * .5f;
                            const auto position = Vector2{particle.x - originX, particle.y - originY};
                            DrawTextureEx(*particle.texture, position, 0, particle.size, Color{
                                              particle.color.r, particle.color.g, particle.color.b, alpha
                                          });
                        } else {
                            it.entity(entityIndex).destruct();
                        }
                    }
                }

                EndBlendMode();
            });
}
