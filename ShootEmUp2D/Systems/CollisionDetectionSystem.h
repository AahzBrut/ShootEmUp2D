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
            .each([query](const flecs::entity entity1, const Collider &collider1) {
                query.each([entity1, collider1](const flecs::entity entity2, const Collider &collider2) {
                    if (entity1 >= entity2) return;
                    if (isIntersects(collider1, collider2) &&
                        CollisionLayersSettings::IsLayersCollides(collider1.layer, collider2.layer)) {
                        entity1.destruct();
                        entity2.destruct();
                    }
                });
            });
}
