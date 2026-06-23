#pragma once
#include "flecs.h"

class Application {
    flecs::world ecsWorld;

public:
    void Run() const;

private:
    void Initialize() const;
    static void DeInitialize();
};
