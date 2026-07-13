#include "tile.h"

Vector2 grid_to_screen(int gridX, int gridY) {
    int screenX = (gridX - gridY)*TILE_WIDTH / 2;
    int screenY = (gridX + gridY)*TILE_HEIGHT / 2;
    return (Vector2){screenX, screenY};
}

void render_tile(Texture2D* atlas, Tile* tile) {
    Rectangle source = (Rectangle){0, 0, 0, 0};
    Vector2 tile_coords = tile->tile_coords;
    TILES tile_type = tile->tile_definition.tile_type;
    switch (tile_type) {
        case EMPTY:
            return;
        // FIRST ROW
        case GRASS:
            source = (Rectangle){2, 1, 29, 30};
            break;
        case DIRT:
            source = (Rectangle){34, 1, 61, 32};
            break;
        // SECOND ROW
        case WATER:
            source = (Rectangle){2, 33, 29, 62};
    }
    DrawTextureRec(*atlas, source, grid_to_screen(tile_coords.x, tile_coords.y), WHITE);
}
