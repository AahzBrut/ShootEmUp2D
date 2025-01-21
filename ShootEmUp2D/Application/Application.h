#pragma once
#include "flecs.h"
#include "TypeDefs.h"
#include "AssetManager/AssetManager.h"

class Application {
    flecs::world ecsWorld;
    Unique<AssetManager> assetManager;
public:
    Application() : assetManager{new AssetManager()} {}

    void Run();

private:
    void Initialize() const;
    void LoadAssets() const;
    void DeInitialize();
};
