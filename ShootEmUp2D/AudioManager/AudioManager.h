#pragma once
#include <raylib.h>
#include "TypeDefs.h"

class AudioManager {
    List<Pair<Shared<Sound>, Sound>> sounds{};

    public:
    void PlaySoundEffect(const Shared<Sound> &sound);
    void Update();
};
