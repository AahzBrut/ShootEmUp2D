#pragma once
#include "flecs.h"

class Application {
    flecs::world ecsWorld;
public:

    void Initialize() const;
    void Run() const;
    void DeInitialize();
};
