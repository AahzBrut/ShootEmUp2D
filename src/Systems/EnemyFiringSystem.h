#pragma once
#include <cmath>

#include <flecs.h>

inline void EnemyFiringSystem(const flecs::world &ecsWorld) {
    const auto query = ecsWorld.query<const Position, const Player>();
    auto assetManager = ecsWorld.get_mut<AssetManager>();
    auto audioManager = ecsWorld.get_mut<AudioManager>();

    ecsWorld.system<const Position, const Sprite, AutoCanon>()
            .each([&ecsWorld, query, assetManager, audioManager](const flecs::iter &it, size_t,
                                                                 const Position &position,
                                                                 const Sprite &spr,
                                                                 AutoCanon &autoCanon) {
                    const auto deltaTime = it.delta_time();
                    autoCanon.timeSinceLastShot += deltaTime;
                    if (autoCanon.timeSinceLastShot > 1.f / autoCanon.rateOfFire) {
                        autoCanon.timeSinceLastShot = 0;

                        const auto playerEntity = query.find([](const Position &, const Player &) { return true; });
                        if (!playerEntity) return;

                        const auto shotSound = assetManager->GetSoundEffect("laser-gun");
                        audioManager->PlaySoundEffect(shotSound);

                        const auto playerPosition = playerEntity.get<Position>();

                        const auto bulletTexture = autoCanon.bulletTexture;
                        const auto bulletPosX = position.x - toFloat(bulletTexture->width);
                        const auto bulletPosY = position.y + toFloat(spr.sprite->height) / 2 -
                                                toFloat(bulletTexture->height) / 2;

                        const auto bulletOffsetX = playerPosition->x - bulletPosX;
                        const auto bulletOffsetY = playerPosition->y - bulletPosY;
                        const auto distance = sqrtf(bulletOffsetX * bulletOffsetX + bulletOffsetY * bulletOffsetY);
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
                                        toFloat(bulletTexture->width),
                                        toFloat(bulletTexture->height),
                                        CollisionLayer::EnemyBullet
                                    };
                                })
                                .add<Bullet>();
                    }
                }
            );
}
