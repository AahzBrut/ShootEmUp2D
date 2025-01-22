#pragma once
#include <flecs.h>

#include "Bullet.h"
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
}
