#include "Application/Application.h"

#include <raylib.h>

#include "defs.h"
#include "Components/Components.h"
#include "Systems/Systems.h"


void Application::Initialize() const {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shoot 'em up");

    RegisterComponents(ecsWorld);
    RegisterSystems(ecsWorld);

    ecsWorld.set(AssetManager{});
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
