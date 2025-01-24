#pragma once
#include "raylib.h"
#include "TypeDefs.h"


struct Debris {
    Vector2 position;
    Vector2 velocity;
    Rectangle textureRect;
    float rotation;
    float rotationSpeed;
    float lifeTimeLeft;
    Shared<Texture2D> texture;
};
