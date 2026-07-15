#include "entity.h"

void render_entity(Texture2D *atlas, Entity *entity) {
    Rectangle source = (Rectangle){0, 0, 0, 0};
    Vector2 entity_coords = entity->entity_coords;
    ENTITY entity_type = entity->entity_definition.entity_type;
    switch (entity_type) {
        case BIG_TREE:
            source = (Rectangle){0, 0, 64, 64};
            break;
        default:
            return;
    }
    Vector2 gridPos = grid_to_screen(entity_coords.x, entity_coords.y);
    Vector2 drawPos = grid_to_draw_pos(entity_coords, source.width, source.height);
    DrawCircleV(gridPos, 1.0f, BLACK);
    DrawTextureRec(*atlas, source, drawPos, WHITE);
}
