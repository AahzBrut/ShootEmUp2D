#include "Application/Application.h"

#include <raylib.h>

#include "defs.h"
#include "Components/Components.h"
#include "Components/Position.h"
#include "Components/Velocity.h"
#include "Systems/Systems.h"


void Application::Initialize() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shoot 'em up");

    LoadAssets();
    RegisterComponents(ecsWorld);
    RegisterSystems(ecsWorld, assetManager);

    // ReSharper disable once CppExpressionWithoutSideEffects
    ecsWorld.entity()
            .insert([this](Position &p, Velocity &v, Sprite &s, Player &pl) {
                p = {10, 20};
                v = {60, 60};
                s = {assetManager.GetTexture("player")};
                pl = { 100 };
            });

    // ReSharper disable once CppExpressionWithoutSideEffects
    ecsWorld.entity()
            .insert([this](Position &p, Velocity &v, Sprite &s) {
                p = {1000, 20};
                v = {-60, 60};
                s = {assetManager.GetTexture("player")};
            });
}

void Application::LoadAssets() {
    assetManager.LoadTexture("player", "./assets/gfx/player.png");
    assetManager.LoadTexture("bullet", "./assets/gfx/playerBullet.png");
}

void Application::Run() {
    Initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        ecsWorld.progress(GetFrameTime());

        char stringBuffer[16];
        sprintf(&stringBuffer[0], "%d", GetFPS());
        DrawText(stringBuffer, 10, 10, 48, WHITE);

        EndDrawing();
    }
    DeInitialize();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Application::DeInitialize() {
    CloseWindow();
}
