#pragma once
#include <flecs.h>

#include "Components/Collider.h"
#include "Components/Sprite.h"

inline bool isIntersects(const Collider &collider1, const Collider &collider2) {
    return collider1.x < collider2.x + collider2.w &&
           collider1.x + collider1.w > collider2.x &&
           collider1.y < collider2.y + collider2.h &&
           collider1.y + collider1.h > collider2.y;
}

inline void SpawnDebris(const flecs::world &ecsWorld, const flecs::entity entity, const Collider &collider) {
    const auto sprite = entity.get<Sprite>()->sprite;
    const auto width = sprite->width / DEBRIS_NUM_SLICES;
    const auto height = sprite->height / DEBRIS_NUM_SLICES;
    const auto velocity = entity.get<Velocity>();
    for (auto x = 0; x < width * DEBRIS_NUM_SLICES; x += width) {
        for (auto y = 0; y < height * DEBRIS_NUM_SLICES; y += height) {
            // ReSharper disable once CppExpressionWithoutSideEffects
            ecsWorld
                    .entity()
                    .insert([&](Debris &debris) {
                        debris = {
                            {collider.x + toFloat(x), collider.y + toFloat(y)},
                            {
                                velocity->x + RandomRange(-30, 30),
                                velocity->y + RandomRange(-100, 100)
                            },
                            Rectangle(toFloat(x), toFloat(y), toFloat(width - 1), toFloat(height - 1)),
                            0.f,
                            RandomRange(-PI * 4, PI * 4),
                            RandomRange(2.5f, 5.f),
                            sprite
                        };
                    });
        }
    }
}

inline void SpawnPointsPickup(const flecs::world &ecsWorld, AssetManager *assetManager, const Collider &collider) {
    // ReSharper disable once CppExpressionWithoutSideEffects
    ecsWorld
            .entity()
            .insert([&](Position &position, Velocity &velocity, Collider &coll, Sprite &sprite, PointsPickup &pointsPickup) {
                position = {collider.x, collider.y};
                velocity = {-100.f, 0.f};
                coll = {collider.x, collider.y, 36,36, CollisionLayer::PointsPickup};
                sprite = {assetManager->GetTexture("points-pickup")};
                pointsPickup = {100};
            });
}

inline void CollisionDetectionSystem(const flecs::world &ecsWorld) {
    const auto query = ecsWorld.query<const Collider>();
    const auto playerQuery = ecsWorld.query<Player>();
    auto assetManager = ecsWorld.get_mut<AssetManager>();
    auto audioManager = ecsWorld.get_mut<AudioManager>();

    ecsWorld.system<const Collider>()
            .each([&ecsWorld, assetManager, audioManager, query, playerQuery](
            const flecs::entity entity1, const Collider &collider1) {
                    query.each([&ecsWorld, assetManager, audioManager, entity1, collider1, playerQuery](
                    const flecs::entity entity2, const Collider &collider2) {
                            if (entity1 >= entity2) return;
                            if (isIntersects(collider1, collider2) &&
                                CollisionLayersSettings::IsLayersCollides(collider1.layer, collider2.layer)) {
                                if (collider1.layer == CollisionLayer::Player && collider2.layer ==
                                    CollisionLayer::PointsPickup ||
                                    collider1.layer == CollisionLayer::PointsPickup && collider2.layer ==
                                    CollisionLayer::Player) {
                                    if (const auto playerEntity = playerQuery.find([](Player &) { return true; })) {
                                        const auto player = playerEntity.get_mut<Player>();
                                        const auto pickupEntity = entity1.has<PointsPickup>() ? entity1 : entity2;
                                        player->score += pickupEntity.get<PointsPickup>()->pointsAmount;
                                        pickupEntity.destruct();
                                        audioManager->PlaySoundEffect(assetManager->GetSoundEffect("notification"));
                                        return;
                                    }
                                }

                                // ReSharper disable once CppExpressionWithoutSideEffects
                                ecsWorld
                                        .entity()
                                        .insert([&](Explode &explode) {
                                            explode = {
                                                std::fmaxf(collider1.x, collider2.x),
                                                std::fmaxf(collider1.y, collider2.y)
                                            };
                                        });

                                if (collider1.layer == CollisionLayer::Enemy) SpawnPointsPickup(
                                    ecsWorld, assetManager, collider1);
                                if (collider2.layer == CollisionLayer::Enemy) SpawnPointsPickup(
                                    ecsWorld, assetManager, collider2);
                                if (!entity1.has<Bullet>()) SpawnDebris(ecsWorld, entity1, collider1);
                                if (!entity2.has<Bullet>()) SpawnDebris(ecsWorld, entity2, collider2);

                                entity1.destruct();
                                entity2.destruct();
                            }
                        });
                });
}
