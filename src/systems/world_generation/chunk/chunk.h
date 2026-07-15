#ifndef CHUNK_H
#define CHUNK_H

#include "raylib.h"
#include "tile/tile.h"
#include "entity/entity.h"

#define CHUNK_SIZE 16
#define TILE_COUNT (CHUNK_SIZE * CHUNK_SIZE)

typedef struct Chunk {
    Vector2 chunk_coords;
    Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
    Entity *entities;
    int entity_count;
    int entity_capacity;
} Chunk;

void render_chunk_tiles(Chunk *chunk, Texture2D *tile_atlas);

// UTIL

Tile *get_tile(Chunk *chunk, Vector2 tile_coords);
void set_tile(Chunk *chunk, Vector2 tile_coords, TILES tile_type);

Entity *get_entity(Chunk *chunk, Vector2 entity_coords);
void set_entity(Chunk *chunk, Vector2 entity_coords, ENTITY entity_type);
void delete_entity(Chunk *chunk, Vector2 entity_coords);

void dispose_chunk(Chunk *chunk);

#endif
