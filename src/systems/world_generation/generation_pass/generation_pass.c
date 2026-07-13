#include "generation_pass.h"

void generate_terrain(Chunk* chunk, WorldConfig* config) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            int tile_x = chunk->chunk_coords.x * CHUNK_SIZE + x;
            int tile_y = chunk->chunk_coords.y * CHUNK_SIZE + y;
            float noise_value = fnlGetNoise2D(config->noise, tile_x, tile_y);
            if (noise_value <= WATER_THRESHOLD) {
                set_tile(chunk, (Vector2){tile_x, tile_y}, WATER);
            } else if (noise_value <= DIRT_THRESHOLD) {
                set_tile(chunk, (Vector2){tile_x, tile_y}, DIRT);
            } else {
                set_tile(chunk, (Vector2){tile_x, tile_y}, GRASS);
            }
        }
    }
}
