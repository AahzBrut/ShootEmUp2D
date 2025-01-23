#pragma once
#include "raylib.h"
#include "TypeDefs.h"
#include "Physics/CollisionLayersSettings.h"


struct AutoCanon {
    float rateOfFire;
    float timeSinceLastShot;
    float bulletSpeed;
    Shared<Texture2D> bulletTexture;
    CollisionLayer bulletCollisionLayer;
};
