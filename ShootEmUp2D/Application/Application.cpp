#include "Application/Application.h"

#include <raylib.h>

#include "defs.h"
#include "Components/Position.h"
#include "Components/Velocity.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"


void Application::Initialize() const {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shoot 'em up");

    MovementSystem(ecsWorld);
    RenderSystem(ecsWorld);

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

void Application::Run() const {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        ecsWorld.progress(GetFrameTime());

        char stringBuffer[16];
        sprintf(&stringBuffer[0], "%d", GetFPS());
        DrawText(stringBuffer, 10, 10, 48, WHITE);

        EndDrawing();
    }
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Application::DeInitialize() {
    CloseWindow();
}
