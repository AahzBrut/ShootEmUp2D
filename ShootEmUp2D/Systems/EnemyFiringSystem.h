#pragma once
#include <flecs.h>
#include <math.h>

inline void EnemyFiringSystem(const flecs::world &ecsWorld) {
    const auto query = ecsWorld.query<const Position, const Player>();

    ecsWorld.system<const Position, const Sprite, AutoCanon>()
            .each([&ecsWorld, query](const flecs::iter &it, size_t,
                                     const Position &position,
                                     const Sprite &spr,
                                     AutoCanon &autoCanon) {
                    const auto deltaTime = it.delta_time();
                    autoCanon.timeSinceLastShot += deltaTime;
                    if (autoCanon.timeSinceLastShot > 1.f / autoCanon.rateOfFire) {
                        autoCanon.timeSinceLastShot = 0;

                        const auto playerEntity = query.find([](const Position, const Player) { return true; });
                        if (!playerEntity) return;
                        const auto playerPosition = playerEntity.get<Position>();

                        const auto bulletTexture = autoCanon.bulletTexture;
                        const auto bulletPosX = position.x - static_cast<float>(bulletTexture->width);
                        const auto bulletPosY = position.y + static_cast<float>(spr.sprite->height) / 2 -
                                                static_cast<float>(bulletTexture->height) / 2;

                        const auto bulletOffsetX = playerPosition->x - bulletPosX;
                        const auto bulletOffsetY = playerPosition->y - bulletPosY;
                        const auto distance = sqrt(bulletOffsetX * bulletOffsetX + bulletOffsetY * bulletOffsetY);
                        const auto bulletVelocityX = bulletOffsetX * autoCanon.bulletSpeed / distance;
                        const auto bulletVelocityY = bulletOffsetY * autoCanon.bulletSpeed / distance;

                        // ReSharper disable once CppExpressionWithoutSideEffects
                        ecsWorld.entity()
                                .insert([&](Position &bulletPos, Velocity &bulletVelocity,
                                            Sprite &sprite, Collider &collider) {
                                    bulletPos = {bulletPosX, bulletPosY};
                                    bulletVelocity = {bulletVelocityX, bulletVelocityY};
                                    sprite = {bulletTexture};
                                    collider = {
                                        bulletPosX, bulletPosY,
                                        static_cast<float>(bulletTexture->width),
                                        static_cast<float>(bulletTexture->height),
                                        CollisionLayer::EnemyBullet
                                    };
                                })
                                .add<Bullet>();
                    }
                }
            );
}
