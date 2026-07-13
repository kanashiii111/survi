#include "chunk.h"
#include "entity/entity.h"
#include <stdlib.h>

void render_chunk(Chunk *chunk, Texture2D *tile_atlas, Texture2D *entity_atlas) {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            render_tile(tile_atlas, &chunk->tiles[i][j]);
        }
    }
    for (int i = 0; i < chunk->entity_count; i++) {
        render_entity(entity_atlas, &chunk->entities[i]);
    }
}

Tile *get_tile(Chunk *chunk, Vector2 tile_coords) {
    int local_x = (int)tile_coords.x - (int)(chunk->chunk_coords.x * CHUNK_SIZE);
    int local_y = (int)tile_coords.y - (int)(chunk->chunk_coords.y * CHUNK_SIZE);
    return &chunk->tiles[local_x][local_y];
}

void set_tile(Chunk *chunk, Vector2 tile_coords, TILES tile_type) {
    int local_x = (int)tile_coords.x - (int)(chunk->chunk_coords.x * CHUNK_SIZE);
    int local_y = (int)tile_coords.y - (int)(chunk->chunk_coords.y * CHUNK_SIZE);
    chunk->tiles[local_x][local_y].tile_coords = tile_coords;
    chunk->tiles[local_x][local_y].tile_definition.tile_type = tile_type;
    chunk->tiles[local_x][local_y].tile_definition.is_solid = !((tile_type == EMPTY) || (tile_type == WATER));
}

Entity *get_entity(Chunk *chunk, Vector2 entity_coords) {
    for (int i = 0; i < chunk->entity_count; i++) {
        if (chunk->entities[i].entity_coords.x == entity_coords.x && chunk->entities[i].entity_coords.y == entity_coords.y) {
            return &chunk->entities[i];
        }
    }
    return NULL;
}

void set_entity(Chunk *chunk, Vector2 entity_coords, ENTITY entity_type) {
    if (chunk->entity_capacity - chunk->entity_count == 0) {
        chunk->entities = realloc(chunk->entities, sizeof(Entity) * chunk->entity_capacity * 2);
        if (chunk->entities == NULL) {
            TraceLog(LOG_FATAL, "chunk.c : failed allocation of memory for entities");
            chunk->entity_count = 0;
            chunk->entity_capacity = 0;
        };
        chunk->entity_capacity *= 2;
    }
    chunk->entities[chunk->entity_count].collision_box =
        (Rectangle){entity_coords.x - 64,
                    entity_coords.y - 64,
                    64,
                    64
    };
    chunk->entities[chunk->entity_count].entity_coords = entity_coords;
    chunk->entities[chunk->entity_count].entity_definition.entity_type = entity_type;
    chunk->entity_count++;
}

void dispose_chunk(Chunk *chunk) {
    free(chunk->entities);
}
