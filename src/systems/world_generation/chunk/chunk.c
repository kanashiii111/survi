#include "chunk.h"

void render_chunk(Chunk* chunk, Texture2D* atlas) {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            render_tile(atlas, &chunk->tiles[i][j]);
        }
    }
}

Tile* get_tile(Chunk* chunk, Vector2 tile_coords) {
    int local_x = (int)tile_coords.x - (int)(chunk->chunk_coords.x * CHUNK_SIZE);
    int local_y = (int)tile_coords.y - (int)(chunk->chunk_coords.y * CHUNK_SIZE);
    return &chunk->tiles[local_x][local_y];
}

void set_tile(Chunk* chunk, Vector2 tile_coords, TILES tile_type) {
    int local_x = (int)tile_coords.x - (int)(chunk->chunk_coords.x * CHUNK_SIZE);
    int local_y = (int)tile_coords.y - (int)(chunk->chunk_coords.y * CHUNK_SIZE);
    chunk->tiles[local_x][local_y].tile_coords = tile_coords;
    chunk->tiles[local_x][local_y].tile_definition.tile_type = tile_type;
    chunk->tiles[local_x][local_y].tile_definition.is_solid = !((tile_type == EMPTY) || (tile_type == WATER));
}
