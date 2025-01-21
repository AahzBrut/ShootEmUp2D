#pragma once
#include "flecs.h"

class Application {
    flecs::world ecsWorld;
public:

    void Run();

private:
    void Initialize() const;
    void DeInitialize();
};
