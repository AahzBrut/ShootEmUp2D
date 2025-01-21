#pragma once
#include "flecs.h"
#include "AssetManager/AssetManager.h"

class Application {
    flecs::world ecsWorld;
    AssetManager assetManager;

public:
    void Run();

private:
    void Initialize();
    void LoadAssets();
    void DeInitialize();
};
