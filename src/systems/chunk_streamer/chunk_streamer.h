#ifndef CHUNK_STREAMER_H
#define CHUNK_STREAMER_H

#include "raylib.h"

typedef struct GameContext GameContext;
typedef struct WorldManager WorldManager;
typedef struct Player Player;

typedef struct ChunkStreamer {
    Vector2 current_chunk_coords;
    Vector2 last_chunk_coords;
} ChunkStreamer;

void init_cs(GameContext *gc, WorldManager *wm, ChunkStreamer* cs, Player *player);
void process_cs(GameContext *gc, WorldManager *wm, ChunkStreamer *cs, Player *player);
void load_chunks(GameContext *gc, WorldManager *wm, ChunkStreamer *cs);
void unload_chunks(GameContext *gc, WorldManager *wm, ChunkStreamer *cs);

#endif
