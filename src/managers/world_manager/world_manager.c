#include "world_manager.h"

#include <stdlib.h>
#include <math.h>
#include "../../systems/world_generation/generation_pass/generation_pass.h"

void create_chunk(GameContext *gc, WorldManager* wm, Vector2 chunk_coords){
    for (unsigned int i = 0; i < wm->rendered_chunks_count; i++) {
        Chunk rendered_chunk = wm->rendered_chunks[i];
        if ((int)rendered_chunk.chunk_coords.x == (int)chunk_coords.x && (int)rendered_chunk.chunk_coords.y == (int)chunk_coords.y) {
            return;
        }
    }
    Chunk chunk = { 0 };
    chunk.chunk_coords = chunk_coords;
    chunk.entities = malloc(sizeof(Entity) * 16);
    chunk.entity_count = 0;
    chunk.entity_capacity = 16;
    generate_terrain(&chunk, wm->config);
    generate_entities(&chunk, wm->config);
    wm->rendered_chunks[wm->rendered_chunks_count++] = chunk;
};

int compare_chunks(const void *a, const void *b) {
    Vector2 ca = ((Chunk*)a)->chunk_coords;
    Vector2 cb = ((Chunk*)b)->chunk_coords;
    float sum_a = ca.x + ca.y;
    float sum_b = cb.x + cb.y;
    if (sum_a < sum_b) return -1;
    if (sum_a > sum_b) return 1;
    return 0;
}

void render_chunks(GameContext *gc, WorldManager *wm) {
    qsort(wm->rendered_chunks, wm->rendered_chunks_count, sizeof(Chunk), compare_chunks);
    for (int i = 0; i < wm->rendered_chunks_count; i++) {
        render_chunk(&wm->rendered_chunks[i], gc->tile_atlas, gc->entity_atlas);
    }
}

void delete_chunk(GameContext *gc, WorldManager* wm, Vector2 chunk_coords) {
    for (unsigned int i = 0; i < wm->rendered_chunks_count; i++) {
        Chunk rendered_chunk = wm->rendered_chunks[i];
        if ((int)rendered_chunk.chunk_coords.x == (int)chunk_coords.x && (int)rendered_chunk.chunk_coords.y == (int)chunk_coords.y) {
            wm->rendered_chunks[i] = wm->rendered_chunks[wm->rendered_chunks_count - 1];
            wm->rendered_chunks_count--;
            return;
        }
    }
}

Chunk* get_chunk(WorldManager* wm, Vector2 chunk_coords) {
    for (unsigned int i = 0; i < wm->rendered_chunks_count; i++) {
        Chunk rendered_chunk = wm->rendered_chunks[i];
        if (rendered_chunk.chunk_coords.x == chunk_coords.x && rendered_chunk.chunk_coords.y == chunk_coords.y) {
            return &wm->rendered_chunks[i];
        }
    }
    return NULL;
};

Vector2 player_pos_to_chunk_coords(Player *player) {
    float screenX = player->camera->target.x;
    float screenY = player->camera->target.y;
    float tileX = screenX / (float)TILE_WIDTH + screenY / (float)TILE_HEIGHT;
    float tileY = screenY / (float)TILE_HEIGHT - screenX / (float)TILE_WIDTH;
    return (Vector2){ floorf(tileX / (float)CHUNK_SIZE), floorf(tileY / (float)CHUNK_SIZE) };
}
