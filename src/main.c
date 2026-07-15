#define FNL_IMPL
#include "raylib.h"
#include "entities/player/player.h"
#include "entities/cat/cat.h"
#include "managers/game_context/game_context.h"
#include "managers/world_manager/world_manager.h"
#include "systems/chunk_streamer/chunk_streamer.h"
#include "systems/world_generation/world_config/world_config.h"
#include <stdlib.h>

bool DEBUG = false;

int main(void) {

    // INIT WINDOW

    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "Survi");

    SetTargetFPS(60);

    // INIT GAME

    GameContext gc;
    WorldManager wm;
    ChunkStreamer cs;
    WorldConfig wc;
    Player *player;
    Cat cat = (Cat){ 0 };

    Texture2D tile_atlas = LoadTexture("src/resources/tileset.png");
    Texture2D entity_atlas = LoadTexture("src/resources/entities.png");
    Texture2D player_atlas = LoadTexture("src/resources/player.png");
    Texture2D cat_atlas = LoadTexture("src/resources/cat.png");
    gc = (GameContext){ 0 };
    gc.tile_atlas = &tile_atlas;
    gc.entity_atlas = &entity_atlas;
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

    RenderTexture2D tiles = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D entities = LoadRenderTexture(screenWidth, screenHeight);

    // Main game loop
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_G)) DEBUG = !DEBUG;

        // Update

        process_player(player, &wm);
        process_cs(&gc, &wm, &cs, player);

        // Render to the texture

        BeginTextureMode(tiles);
            ClearBackground(BLANK);
            BeginMode2D(*player->camera);
                wm_render_tiles(&gc, &wm);
            EndMode2D();
        EndTextureMode();

        BeginTextureMode(entities);
            ClearBackground(BLANK);
            BeginMode2D(*player->camera);
                wm_render_entities(&gc, &wm);
                if (DEBUG) {
                    draw_interact_debug(player, &wm);
                    draw_mouse_pos_debug(player);
                    draw_player_pos_debug(player);
                }
            EndMode2D();
        EndTextureMode();

        // Draw to screen
        BeginDrawing();
            ClearBackground(BLANK);
            DrawTextureRec(tiles.texture, (Rectangle){0, 0, tiles.texture.width, -tiles.texture.height}, (Vector2) {0, 0}, WHITE);
            DrawTextureRec(entities.texture, (Rectangle){0, 0, entities.texture.width, -entities.texture.height}, (Vector2) {0, 0}, WHITE);
        EndDrawing();
    }

    // De-Initialization

    dispose_player(player);
    UnloadRenderTexture(tiles);
    UnloadRenderTexture(entities);

    CloseWindow();

    return 0;
}
