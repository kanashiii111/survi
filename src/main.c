#define FNL_IMPL
#include "../third_party/include/raylib.h"
#include "entities/player/player.h"
#include "entities/cat/cat.h"
#include "managers/game_context/game_context.h"
#include "managers/world_manager/world_manager.h"
#include "systems/chunk_streamer/chunk_streamer.h"
#include "systems/world_generation/world_config/world_config.h"
#include <stdlib.h>

int main(void) {

    // INIT WINDOW

    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    // INIT GAME

    GameContext gc;
    WorldManager wm;
    ChunkStreamer cs;
    WorldConfig wc;
    Player *player;
    Cat cat = (Cat){ 0 };

    Texture2D tile_atlas = LoadTexture("src/resources/tileset.png");
    Texture2D player_atlas = LoadTexture("src/resources/player.png");
    Texture2D cat_atlas = LoadTexture("src/resources/cat.png");
    gc = (GameContext){ 0 };
    gc.tile_atlas = &tile_atlas;
    gc.player_atlas = &player_atlas;
    gc.cat_atlas = &cat_atlas;

    fnl_state noise = fnlCreateState();
    wc.noise = &noise;
    wc.seed = 100;

    wm = (WorldManager){ 0 };
    wm.config = &wc;

    player = malloc(sizeof(Player));
    wm.player = player;


    init_player(&gc, player);
    init_cat(&gc, &cat);
    init_cs(&gc, &wm, &cs, player);


    // Main game loop
    while (!WindowShouldClose()) {
        // Update

        process_player(player);
        process_cs(&gc, &wm, &cs, player);

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(*player->camera);

                render_chunks(&gc, &wm);
                render_player(player);
                render_cat(&cat);

            EndMode2D();


        EndDrawing();
    }

    // De-Initialization

    dispose_player(player);

    CloseWindow();

    return 0;
}
