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
    DrawTextureRec(*atlas, source, grid_to_screen(entity_coords.x, entity_coords.y), WHITE);
}
