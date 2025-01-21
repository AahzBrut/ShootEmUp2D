#include "Application/Application.h"

#include <raylib.h>

#include "defs.h"
#include "Components/Components.h"
#include "Components/Position.h"
#include "Components/Velocity.h"
#include "Systems/Systems.h"


void Application::Initialize() const {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shoot 'em up");

    RegisterComponents(ecsWorld);
    RegisterSystems(ecsWorld);

    // ReSharper disable once CppExpressionWithoutSideEffects
    ecsWorld.entity()
            .insert([](Position &p, Velocity &v) {
                p = {10, 20};
                v = {60, 60};
            });

    // ReSharper disable once CppExpressionWithoutSideEffects
    ecsWorld.entity()
            .insert([](Position &p, Velocity &v) {
                p = {1000, 20};
                v = {-60, 60};
            });
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
