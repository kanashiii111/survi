#ifndef CHUNK
#define CHUNK

#include "../../../../third_party/include/raylib.h"
#include "tile/tile.h"
#include "tile/tile_definition/tile_definition.h"

#define CHUNK_SIZE 16
#define TILE_COUNT (CHUNK_SIZE * CHUNK_SIZE)

typedef struct Chunk {
    Vector2 chunk_coords;
    Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
} Chunk;

void render_chunk(Chunk* chunk, Texture2D* atlas);
Tile* get_tile(Chunk* chunk, Vector2 tile_coords);
void set_tile(Chunk* chunk, Vector2 tile_coords, TILES tile_type);

#endif
