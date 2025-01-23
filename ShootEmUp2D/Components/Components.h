#pragma once
#include <flecs.h>

#include "AutoCanon.h"
#include "Background.h"
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
    ecsWorld.component<Collider>();
    ecsWorld.component<AutoCanon>();
    ecsWorld.component<Background>();
    ecsWorld.component<Star>();
}
