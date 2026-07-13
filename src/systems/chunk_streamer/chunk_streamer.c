#include "chunk_streamer.h"

void init_cs(GameContext *gc, WorldManager *wm, ChunkStreamer *cs, Player *player) {
    cs->current_chunk_coords = player_pos_to_chunk_coords(player);
    cs->last_chunk_coords = cs->current_chunk_coords;
    load_chunks(gc, wm, cs);
}

void process_cs(GameContext *gc, WorldManager *wm, ChunkStreamer *cs, Player *player) {
    Vector2 new_coords = player_pos_to_chunk_coords(player);
    if (!(new_coords.x == cs->last_chunk_coords.x && new_coords.y == cs->last_chunk_coords.y)) {
        cs->last_chunk_coords = new_coords;
        cs->current_chunk_coords = new_coords;
        load_chunks(gc, wm, cs);
    }
}

void load_chunks(GameContext *gc, WorldManager *wm, ChunkStreamer *cs) {
    int rd = RENDER_DISTANCE;
    unload_chunks(gc, wm, cs);
    for (int x = -rd; x <= rd; x++) {
        for (int y = -rd; y <= rd; y++) {
            Vector2 coords = Vector2Add(cs->current_chunk_coords, (Vector2){x, y});
            if (!(get_chunk(wm, coords))) {
                create_chunk(gc, wm, coords);
            }
        }
    }
}

void unload_chunks(GameContext *gc, WorldManager *wm, ChunkStreamer *cs) {
    int rd = RENDER_DISTANCE;
    for (int i = wm->rendered_chunks_count - 1; i >= 0; i--) {
        Vector2 chunk_pos = wm->rendered_chunks[i].chunk_coords;
        Vector2 rel = Vector2Subtract(chunk_pos, cs->current_chunk_coords);
        if (rel.x < -rd || rel.x > rd || rel.y < -rd || rel.y > rd) {
            delete_chunk(gc, wm, chunk_pos);
        }
    }
}
