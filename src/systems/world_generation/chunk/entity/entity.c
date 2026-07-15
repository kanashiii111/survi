#include "entity.h"
#include "../tile/tile.h"
#include "../tile/tile.h"

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
    Vector2 drawPos = grid_to_draw_pos(entity_coords, source.width, source.height);
    DrawTextureRec(*atlas, source, drawPos, WHITE);
}

// <----------------DEBUG---------------->

void draw_debug_shapes(Entity *entity, Color circle_color, Color interact_box_color) {
    Rectangle source = (Rectangle){0, 0, 0, 0};
    Vector2 gridPos = grid_to_screen(entity->entity_coords.x, entity->entity_coords.y);
    Vector2 drawPos = grid_to_draw_pos(entity->entity_coords, source.width, source.height);
    DrawCircleV(gridPos, 1.0f, circle_color);

    Vector2 coll_box_draw_pos = grid_to_draw_pos((Vector2){entity->interact_box.x, entity->interact_box.y}, entity->interact_box.width, entity->interact_box.height);
    DrawRectangleLinesEx((Rectangle){coll_box_draw_pos.x, coll_box_draw_pos.y, entity->interact_box.width, entity->interact_box.height}, 1.0f, interact_box_color);
}
