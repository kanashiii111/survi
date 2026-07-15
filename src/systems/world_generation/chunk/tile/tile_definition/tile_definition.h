#ifndef TILE_DEFINITION_H
#define TILE_DEFINITION_H

#include <stdbool.h>

typedef enum TILES {
    EMPTY = -1,
    GRASS,
    DIRT,
    WATER
} TILES;

typedef struct TileDefinition {
    TILES tile_type;
    bool is_solid;
} TileDefinition;

#endif
