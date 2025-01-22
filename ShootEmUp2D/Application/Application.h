#pragma once
#include "flecs.h"
#include "AssetManager/AssetManager.h"

class Application {
    flecs::world ecsWorld;

public:
    void Run();

private:
    void Initialize() const;
    void DeInitialize();
};
