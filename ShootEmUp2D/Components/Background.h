#pragma once
#include <raylib.h>

#include "TypeDefs.h"


struct Background {
    Shared<Texture2D> sprite;
    float scrollSpeed;
    float offset;
};
