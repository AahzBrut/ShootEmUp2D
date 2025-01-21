#include "Application/Application.h"

#include <raylib.h>

#include "defs.h"
#include "Components/Components.h"
#include "Components/Position.h"
#include "Components/Velocity.h"
#include "Systems/Systems.h"


void Application::Initialize() const {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shoot 'em up");

    LoadAssets();
    RegisterComponents(ecsWorld);
    RegisterSystems(ecsWorld);

    // ReSharper disable once CppExpressionWithoutSideEffects
    ecsWorld.entity()
            .insert([this](Position &p, Velocity &v, Sprite &s) {
                p = {10, 20};
                v = {60, 60};
                s = { assetManager.get()->GetTexture("player")};
            });

    // ReSharper disable once CppExpressionWithoutSideEffects
    ecsWorld.entity()
            .insert([this](Position &p, Velocity &v, Sprite &s) {
                p = {1000, 20};
                v = {-60, 60};
                s = { assetManager.get()->GetTexture("player")};
            });
}

void Application::LoadAssets() const {
    assetManager.get()->LoadTexture("player", "./assets/gfx/player.png");
}

void Application::Run() {
    Initialize();
    LoadAssets();

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
