#ifndef TILE
#define TILE

#include "../../../../../third_party/include/raylib.h"
#include "tile_definition/tile_definition.h"

#define TILE_WIDTH 28
#define TILE_HEIGHT 14

typedef struct Tile {
    Vector2 tile_coords;
    TileDefinition tile_definition;
} Tile;

void render_tile(Texture2D* atlas, Tile* tile);
Vector2 grid_to_screen(int gridX, int gridY);

#endif
