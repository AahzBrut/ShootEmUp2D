#pragma once


struct Star {
    float posX, posY;
    float speed;
    float size;
    Shared<Texture2D> texture;
    Color color;
};
