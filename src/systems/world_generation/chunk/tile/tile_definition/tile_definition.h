#ifndef TILE_DEFINITION
#define TILE_DEFINITION

#include "../../../../../../third_party/include/raylib.h"

typedef enum TILES {
    EMPTY = -1,
    GRASS, // 0
    DIRT, // 1
    WATER // 2
} TILES;

typedef struct TileDefinition {
    TILES tile_type;
    bool is_solid;
} TileDefinition;

#endif
