#pragma once
#include <flecs.h>

#include "Components/Collider.h"

inline bool isIntersects(const Collider &collider1, const Collider &collider2) {
    return collider1.x < collider2.x + collider2.w &&
           collider1.x + collider1.w > collider2.x &&
           collider1.y < collider2.y + collider2.h &&
           collider1.y + collider1.h > collider2.y;
}

inline void CollisionDetectionSystem(const flecs::world &ecsWorld) {
    const auto query = ecsWorld.query<const Collider>();

    ecsWorld.system<const Collider>()
            .each([&ecsWorld, query](const flecs::entity entity1, const Collider &collider1) {
                query.each([&ecsWorld, entity1, collider1](const flecs::entity entity2, const Collider &collider2) {
                    if (entity1 >= entity2) return;
                    if (isIntersects(collider1, collider2) &&
                        CollisionLayersSettings::IsLayersCollides(collider1.layer, collider2.layer)) {
                        // ReSharper disable once CppExpressionWithoutSideEffects
                        ecsWorld
                                .entity()
                                .insert([&](Explode &explode) {
                                    explode = {
                                        std::fmaxf(collider1.x, collider2.x), std::fmaxf(collider1.y, collider2.y)
                                    };
                                });

                        if (!entity1.has<Bullet>()) {
                            const auto sprite = entity1.get<Sprite>()->sprite;
                            const auto width = sprite->width / DEBRIS_NUM_SLICES;
                            const auto height = sprite->height / DEBRIS_NUM_SLICES;
                            const auto velocity = entity1.get<Velocity>();
                            for (auto x = 0; x < width * DEBRIS_NUM_SLICES; x += width) {
                                for (auto y = 0; y < height * DEBRIS_NUM_SLICES; y += height) {
                                    // ReSharper disable once CppExpressionWithoutSideEffects
                                    ecsWorld
                                            .entity()
                                            .insert([&](Debris &debris) {
                                                debris = {
                                                    {collider1.x + x, collider1.y + y},
                                                    {
                                                        velocity->x + RandomRange(-10, 10),
                                                        velocity->y + RandomRange(-10, 10)
                                                    },
                                                    Rectangle(x, y, width - 1, height - 1),
                                                    0.f,
                                                    RandomRange(-2, 2),
                                                    RandomRange(2.5f, 5.f),
                                                    sprite
                                                };
                                            });
                                }
                            }
                        }

                        if (!entity2.has<Bullet>()) {
                            const auto sprite = entity2.get<Sprite>()->sprite;
                            const auto velocity = entity2.get<Velocity>();
                            const auto width = sprite->width / DEBRIS_NUM_SLICES;
                            const auto height = sprite->height / DEBRIS_NUM_SLICES;
                            for (auto x = 0; x < width * DEBRIS_NUM_SLICES; x += width) {
                                for (auto y = 0; y < height * DEBRIS_NUM_SLICES; y += height) {
                                    // ReSharper disable once CppExpressionWithoutSideEffects
                                    ecsWorld
                                            .entity()
                                            .insert([&](Debris &debris) {
                                                debris = {
                                                    {collider2.x + x, collider2.y + y},
                                                    {
                                                        velocity->x + RandomRange(-10, 10),
                                                        velocity->y + RandomRange(-10, 10)
                                                    },
                                                    Rectangle(x, y, width - 1, height - 1),
                                                    0.f,
                                                    RandomRange(-2, 2),
                                                    RandomRange(2.5f, 5.f),
                                                    sprite
                                                };
                                            });
                                }
                            }
                        }

                        entity1.destruct();
                        entity2.destruct();
                    }
                });
            });
}
