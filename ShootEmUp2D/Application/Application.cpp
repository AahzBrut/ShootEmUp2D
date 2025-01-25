#include "Application/Application.h"

#include <raylib.h>

#include "defs.h"
#include "AudioManager/AudioManager.h"
#include "Components/Components.h"
#include "Systems/Systems.h"


void Application::Initialize() const {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shoot 'em up");
    InitAudioDevice();

    RegisterComponents(ecsWorld);
    ecsWorld.set(AssetManager{});
    ecsWorld.set(AudioManager{});
    RegisterSystems(ecsWorld);
}

void Application::Run() {
    Initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        ecsWorld.progress(GetFrameTime());

        char stringBuffer[16];
        sprintf(&stringBuffer[0], "%d", GetFPS());
        DrawText(stringBuffer, 10, 10, 32, WHITE);

        EndDrawing();
    }
    DeInitialize();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Application::DeInitialize() {
    CloseAudioDevice();
    CloseWindow();
}
