#pragma once
#include <flecs.h>

#include "AutoCanon.h"
#include "Background.h"
#include "Debris.h"
#include "Explode.h"
#include "ExplosionParticle.h"
#include "PointsPickup.h"
#include "Star.h"
#include "AssetManager/AssetManager.h"
#include "Components/Bullet.h"
#include "Components/Collider.h"
#include "Components/Player.h"
#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Components/Velocity.h"

// ReSharper disable CppExpressionWithoutSideEffects
inline void RegisterComponents(const flecs::world &ecsWorld) {
    ecsWorld.component<Position>();
    ecsWorld.component<Velocity>();
    ecsWorld.component<Sprite>();
    ecsWorld.component<Player>();
    ecsWorld.component<Bullet>();
    ecsWorld.component<AssetManager>();
    ecsWorld.component<AudioManager>();
    ecsWorld.component<Collider>();
    ecsWorld.component<AutoCanon>();
    ecsWorld.component<Background>();
    ecsWorld.component<Star>();
    ecsWorld.component<ExplosionParticle>();
    ecsWorld.component<Explode>();
    ecsWorld.component<Debris>();
    ecsWorld.component<PointsPickup>();
}
