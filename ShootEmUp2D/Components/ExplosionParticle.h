#pragma once


struct ExplosionParticle {
    float x, y, size;
    float dx, dy;
    float maxSize;
    float maxLifetime, currentLifetime;
    Shared<Texture2D> texture;
    Color color;
};
