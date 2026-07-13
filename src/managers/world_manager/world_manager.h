#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include "../game_context/game_context.h"
#include "../../systems/world_generation/world_config/world_config.h"
#include "../../systems/world_generation/chunk/chunk.h"
#include "../../entities/player/player.h"

#define RENDER_DISTANCE 2
#define MAX_CHUNKS ((2 * RENDER_DISTANCE + 1)*(2 * RENDER_DISTANCE + 1))

typedef struct WorldManager {
    WorldConfig *config;
    Player *player;
    Chunk rendered_chunks[MAX_CHUNKS];
    unsigned int rendered_chunks_count;
} WorldManager;

Chunk* get_chunk(WorldManager* wm, Vector2 chunk_coords);
void create_chunk(GameContext *gc, WorldManager* wm, Vector2 chunk_coords);
void delete_chunk(GameContext *gc, WorldManager* wm, Vector2 chunk_coords);
void render_chunks(GameContext *gc, WorldManager *wm);

Vector2 player_pos_to_chunk_coords(Player *player);

#endif
