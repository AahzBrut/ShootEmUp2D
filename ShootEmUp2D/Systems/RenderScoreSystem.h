#pragma once
#include <flecs.h>
#include <raylib.h>

#include "defs.h"
#include "Components/Player.h"


inline void RenderScoreSystem(const flecs::world &ecsWorld) {
    const auto playerQuery = ecsWorld.query<Player>();

    ecsWorld.system()
            .kind(flecs::OnStore)
            .run([playerQuery](flecs::iter &) {
                static auto score = 0;

                if (const auto playerEntity = playerQuery.find([](Player &) { return true; })) {
                    const auto player = playerEntity.get_mut<Player>();
                    score = player->score;
                }

                char stringBuffer[16];
                sprintf(&stringBuffer[0], "Score: %d", score);
                DrawText(stringBuffer, WINDOW_WIDTH - 180, 10, 32, WHITE);
            });
}
